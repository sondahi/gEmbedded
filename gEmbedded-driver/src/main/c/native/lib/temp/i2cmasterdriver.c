
#include "i2cmasterdriver.h"
#include "i2cmasterexception.h"

#include "common.h"
#include <jni.h>
#include "mapper.h"

#define BSC0_BASE_ADDRESS   (PERIPHERAL_BASE_ADDRESS + 0x205000)
#define BSC1_BASE_ADDRESS   (PERIPHERAL_BASE_ADDRESS + 0x804000)
#define BSC_BLOCK_SIZE      (0x20)

I2CMaster i2CMasterDriver;

typedef struct BSCRegs_ {
    reg C; // Control
    reg S; // Status
    reg DLEN; // Data length
    reg A; // Slave address
    reg FIFO; // Data FIFO
    reg DIV; // Clock divider
    reg DEL; // Data delay
    reg CLKT; // Clock stretch timeout
} BSCRegs;

static BSCRegs *bscRegs[2];

// Control register
#define C_I2C_EN        (1 << 15)
#define C_I2C_DIS       (0 << 15)
#define C_INTR_EN       (1 << 10)
#define C_INTR_DIS      (0 << 10)
#define C_INTT_EN       (1 << 9)
#define C_INTT_DIS      (0 << 9)
#define C_INTD_EN       (1 << 8)
#define C_INTD_DIS      (0 << 8)
#define C_ST            (1 << 7)
#define C_CLEAR         (1 << 4)
#define C_READ          (1 << 0)
#define C_WRITE         (0 << 0)
#define C_RECEIVE       (C_I2C_EN | C_INTR_DIS | C_INTT_DIS | C_INTD_DIS | C_ST | C_CLEAR | C_READ)
#define C_SEND          (C_I2C_EN | C_INTR_DIS | C_INTT_DIS | C_INTD_DIS | C_ST | C_CLEAR | C_WRITE)

// Status register
#define S_CLKT          (1 << 9)
#define S_ERR           (1 << 8)
#define S_RXF           (1 << 7)
#define S_TXE           (1 << 6)
#define S_RXD           (1 << 5)
#define S_TXD           (1 << 4)
#define S_RXR           (1 << 3)
#define S_TXW           (1 << 2)
#define S_DONE          (1 << 1)
#define S_TA            (1 << 0)
#define S_CLEAR         (S_CLKT | S_ERR | S_DONE)

static I2C_STATUS configure_(const jint busSelector, const jint busClockInHertz, const jint busClockStretchTimeout) {

    const register u32 divider = (CORE_CLOCK_SPEED / busClockInHertz);
    bscRegs[busSelector]->DIV = divider;
    const register u32 divider_ = bscRegs[busSelector]->DIV;
    if (divider_ != divider) {
        return I2C_BUS_DIV_ERROR;
    }

    bscRegs[busSelector]->CLKT = busClockStretchTimeout;
    const register u32 busClockStretchTimeout_ = bscRegs[busSelector]->CLKT;
    if (busClockStretchTimeout_ != busClockStretchTimeout) {
        return I2C_BUS_CLKT_ERROR;
    }

    return I2C_SUCCESS;

}

static I2C_STATUS sendData_(struct MessageToSend *sMessage) {

    register int count = 0;

    bscRegs[sMessage->busSelector]->A = sMessage->address;
    bscRegs[sMessage->busSelector]->DLEN = sMessage->dataToSendSize;
    bscRegs[sMessage->busSelector]->S = S_CLEAR;
    bscRegs[sMessage->busSelector]->C = C_SEND;
    while (!(bscRegs[sMessage->busSelector]->S & S_DONE)) {
        while (count < sMessage->dataToSendSize && bscRegs[sMessage->busSelector]->S & S_TXD) {
            bscRegs[sMessage->busSelector]->FIFO = sMessage->dataToSend[count++];
        }
    }

    const register u32 status = bscRegs[sMessage->busSelector]->S;
    if (status & S_ERR) {
        return I2C_SLAVE_SEND_ACK_ERROR;
    } else if (status & S_CLKT) {
        return I2C_SLAVE_SEND_CLOCK_TIMEOUT_ERROR;
    } else if (count < sMessage->dataToSendSize) {
        return I2C_SLAVE_SEND_DATA_LOSS_ERROR;
    }

    return I2C_SUCCESS;

}

static I2C_STATUS receiveData_(struct MessageToReceive *rMessage) {

    register int count = 0;

    bscRegs[rMessage->busSelector]->A = rMessage->address;
    bscRegs[rMessage->busSelector]->DLEN = rMessage->dataToReceiveSize;
    bscRegs[rMessage->busSelector]->S = S_CLEAR;
    bscRegs[rMessage->busSelector]->C = C_RECEIVE;
    while (!(bscRegs[rMessage->busSelector]->S & S_DONE)) {
        while (bscRegs[rMessage->busSelector]->S & S_RXD) {
            rMessage->dataToReceive[count++] = bscRegs[rMessage->busSelector]->FIFO & 0xFF;
        }
    }

    const register u32 status = bscRegs[rMessage->busSelector]->S;
    if (status & S_ERR) {
        return I2C_SLAVE_RECEIVE_ACK_ERROR;
    } else if (status & S_CLKT) {
        return I2C_SLAVE_RECEIVE_CLOCK_TIMEOUT_ERROR;
    } else if (count < rMessage->dataToReceiveSize) {
        return I2C_SLAVE_RECEIVE_DATA_LOSS_ERROR;
    }

    return I2C_SUCCESS;

}

static I2C_STATUS sendAndReceiveData_(struct MessageToSendAndReceive *srMessage) {

    register int count = 0;
    register u32 status;

    bscRegs[srMessage->busSelector]->A = srMessage->address;

    bscRegs[srMessage->busSelector]->DLEN = srMessage->dataToSendSize;
    bscRegs[srMessage->busSelector]->S = S_CLEAR;
    bscRegs[srMessage->busSelector]->C = C_SEND;
    while (!(bscRegs[srMessage->busSelector]->S & S_DONE)) {
        while (count < srMessage->dataToSendSize && bscRegs[srMessage->busSelector]->S & S_TXD) {
            bscRegs[srMessage->busSelector]->FIFO = srMessage->dataToSend[count++];
        }
    }

    status = bscRegs[srMessage->busSelector]->S;
    if (status & S_ERR) {
        return I2C_SLAVE_SEND_ACK_ERROR;
    } else if (status & S_CLKT) {
        return I2C_SLAVE_SEND_CLOCK_TIMEOUT_ERROR;
    } else if (count < srMessage->dataToSendSize) {
        return I2C_SLAVE_SEND_DATA_LOSS_ERROR;
    }

    count = 0;

    bscRegs[srMessage->busSelector]->DLEN = srMessage->dataToReceiveSize;
    bscRegs[srMessage->busSelector]->S = S_CLEAR;
    bscRegs[srMessage->busSelector]->C = C_RECEIVE;
    while (!(bscRegs[srMessage->busSelector]->S & S_DONE)) {
        while (bscRegs[srMessage->busSelector]->S & S_RXD) {
            srMessage->dataToReceive[count++] = bscRegs[srMessage->busSelector]->FIFO & 0xFF;
        }
    }

    status = bscRegs[srMessage->busSelector]->S;
    if (status & S_ERR) {
        return I2C_SLAVE_RECEIVE_ACK_ERROR;
    } else if (status & S_CLKT) {
        return I2C_SLAVE_RECEIVE_CLOCK_TIMEOUT_ERROR;
    } else if (count < srMessage->dataToReceiveSize) {
        return I2C_SLAVE_RECEIVE_DATA_LOSS_ERROR;
    }

    return I2C_SUCCESS;

}

I2C_STATUS i2cMasterDriverSetup(const jint busSelector) {

    off_t physicalAddress;

    switch (busSelector) {
        case 0:
        {
            physicalAddress = BSC0_BASE_ADDRESS;
            break;
        }
        case 1:
        {
            physicalAddress = BSC1_BASE_ADDRESS;
            break;
        }
        default:
        {
            return I2C_UNSUPPORTED_BUS_ERROR;
        }
    }

    void *pointer;
    register MapperStatus mapperStatus;

    mapperStatus = mapBaseRegister(&pointer, MEMORY_FILE_NAME, BSC_BLOCK_SIZE, physicalAddress);
    if (mapperStatus == MAPPER_FILE_OPEN_ERROR) {
        return I2C_BUS_DEV_FILE_OPEN_ERROR;
    } else if (mapperStatus == MAPPER_MEMORY_MAP_ERROR) {
        return I2C_BUS_MEM_MAP_ERROR;
    } else {
        bscRegs[busSelector] = (BSCRegs *) pointer;
    }

    i2CMasterDriver.configure = configure_;
    i2CMasterDriver.sendData = sendData_;
    i2CMasterDriver.receiveData = receiveData_;
    i2CMasterDriver.sendAndReceiveData = sendAndReceiveData_;

    return I2C_SUCCESS;

}

I2C_STATUS i2cMasterDriverShutdown(jint busSelector) {

    BSCRegs* registers;

    switch (busSelector) {
        case 0:
        {
            registers = bscRegs[0];
            break;
        }
        case 1:
        {
            registers = bscRegs[1];
            break;
        }
        default:
        {
            return I2C_UNSUPPORTED_BUS_ERROR;
        }
    }

    bscRegs[busSelector]->C = C_I2C_DIS;

    const register MapperStatus mapperStatus = unmapBaseRegister((void *) registers, BSC_BLOCK_SIZE);
    if (mapperStatus == MAPPER_MEMORY_UNMAP_ERROR) {
        return I2C_BUS_MEM_UNMAP_ERROR;
    }

    return I2C_SUCCESS;

}
