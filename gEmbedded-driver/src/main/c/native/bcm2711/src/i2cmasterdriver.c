#include "i2cmasterdriver.h"
#include "mapper.h"
#include "jnicontroller.h"
#include "bcm2711common.h"

#define BSC0_BASE_ADDRESS       (PERIPHERAL_BASE_ADDRESS + 0x205000)
#define BSC1_BASE_ADDRESS       (PERIPHERAL_BASE_ADDRESS + 0x804000)
#define BSC_BLOCK_SIZE          (0x20)

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

static I2C_STATUS configure_ (const jint busSelector, const jint busClockInHertz, const jint busClockStretchTimeout) {

    const register reg_t divider = (CORE_CLOCK_SPEED / busClockInHertz);
    bscRegs[busSelector]->DIV = divider;
    const register reg_t divider_ = bscRegs[busSelector]->DIV;
    if (divider_ != divider) {
        return I2C_BUS_DIV_ERROR;
    }

    bscRegs[busSelector]->CLKT = busClockStretchTimeout;
    const register reg_t busClockStretchTimeout_ = bscRegs[busSelector]->CLKT;
    if (busClockStretchTimeout_ != busClockStretchTimeout) {
        return I2C_BUS_CLKT_ERROR;
    }

    return I2C_SUCCESS;

}

static jint getRegisterSelector_ (jint busNumber){
    return busNumber;
}

static I2C_STATUS sendData_ (struct MessageToSend *sMessage) {

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

    const register reg_t status = bscRegs[sMessage->busSelector]->S;
    if (status & S_ERR) {
        return I2C_SLAVE_SEND_ACK_ERROR;
    } else if (status & S_CLKT) {
        return I2C_SLAVE_SEND_CLOCK_TIMEOUT_ERROR;
    } else if (count < sMessage->dataToSendSize) {
        return I2C_SLAVE_SEND_DATA_LOSS_ERROR;
    }

    return I2C_SUCCESS;

}

static I2C_STATUS receiveData_ (struct MessageToReceive *rMessage) {

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

    const register reg_t status = bscRegs[rMessage->busSelector]->S;
    if (status & S_ERR) {
        return I2C_SLAVE_RECEIVE_ACK_ERROR;
    } else if (status & S_CLKT) {
        return I2C_SLAVE_RECEIVE_CLOCK_TIMEOUT_ERROR;
    } else if (count < rMessage->dataToReceiveSize) {
        return I2C_SLAVE_RECEIVE_DATA_LOSS_ERROR;
    }

    return I2C_SUCCESS;

}

static I2C_STATUS sendAndReceiveData_ (struct MessageToSendAndReceive *srMessage) {

    register int count = 0;
    register reg_t status;

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

I2C_STATUS i2cMasterDriverSetup () {

    void *pointer;
    register MAPPER_STATUS mapperStatus;

    mapperStatus = mapBaseRegister (BSC0_BASE_ADDRESS, BSC_BLOCK_SIZE, MEMORY_FILE_NAME, &pointer);
    if (mapperStatus == MAPPER_FILE_OPEN_ERROR) {
        return I2C_BUS_DEV_FILE_OPEN_ERROR;
    } else if (mapperStatus == MAPPER_MEMORY_MAP_ERROR) {
        return I2C_BUS_MEM_MAP_ERROR;
    } else {
        bscRegs[0] = (BSCRegs *) pointer;
    }

    mapperStatus = mapBaseRegister (BSC1_BASE_ADDRESS, BSC_BLOCK_SIZE, MEMORY_FILE_NAME, &pointer);
    if (mapperStatus == MAPPER_FILE_OPEN_ERROR) {
        return I2C_BUS_DEV_FILE_OPEN_ERROR;
    } else if (mapperStatus == MAPPER_MEMORY_MAP_ERROR) {
        return I2C_BUS_MEM_MAP_ERROR;
    } else {
        bscRegs[1] = (BSCRegs *) pointer;
    }

    i2CMasterDriver.configure = configure_;
    i2CMasterDriver.getRegisterSelector = getRegisterSelector_;
    i2CMasterDriver.sendData = sendData_;
    i2CMasterDriver.receiveData = receiveData_;
    i2CMasterDriver.sendAndReceiveData = sendAndReceiveData_;

    return I2C_SUCCESS;

}

I2C_STATUS i2cMasterDriverShutdown () {

    bscRegs[0]->C = C_I2C_DIS;
    bscRegs[1]->C = C_I2C_DIS;

    BSCRegs *registers;

    registers = bscRegs[0];

    register MAPPER_STATUS mapperStatus = unmapBaseRegister (BSC_BLOCK_SIZE, (void *) registers);
    if (mapperStatus == MAPPER_MEMORY_UNMAP_ERROR) {
        return I2C_BUS_MEM_UNMAP_ERROR;
    }

    registers = bscRegs[1];

    mapperStatus = unmapBaseRegister (BSC_BLOCK_SIZE, (void *) registers);
    if (mapperStatus == MAPPER_MEMORY_UNMAP_ERROR) {
        return I2C_BUS_MEM_UNMAP_ERROR;
    }

    return I2C_SUCCESS;

}

I2C_STATUS i2cStatusCheck(JNIEnv *env, const I2C_STATUS status){

    switch (status) {
        case I2C_BUS_DEV_FILE_OPEN_ERROR: {
            char message[250]; // performance check
            sprintf(message, "I2C bus device file could not be opened");
            jniController.throwANewJNIException(env, message);
            return I2C_EXCEPTION_OCCURRED;
        }
        case I2C_UNSUPPORTED_BUS_ERROR:{
            char message[250]; // performance check
            sprintf(message, "I2C bus is not supported");
            jniController.throwANewJNIException(env, message);
            return I2C_EXCEPTION_OCCURRED;
        }
        case I2C_BUS_MEM_MAP_ERROR: {
            char message[250]; // performance check
            sprintf(message, "I2C bus memory mapping could not be configured");
            jniController.throwANewJNIException(env, message);
            return I2C_EXCEPTION_OCCURRED;
        }
        case I2C_BUS_MEM_UNMAP_ERROR: {
            char message[250]; // performance check
            sprintf(message, "I2C bus memory unmapping could not be configured");
            jniController.throwANewJNIException(env, message);
            return I2C_EXCEPTION_OCCURRED;
        }
        case I2C_BUS_DIV_ERROR: {
            char message[250]; // performance check
            sprintf(message, "I2C bus divider could not be configured");
            jniController.throwANewJNIException(env, message);
            return I2C_EXCEPTION_OCCURRED;
        }
        case I2C_BUS_CLKT_ERROR: {
            char message[250]; // performance check
            sprintf(message, "I2C clock stretch timeout could not be configured");
            jniController.throwANewJNIException(env, message);
            return I2C_EXCEPTION_OCCURRED;
        }
        case I2C_SLAVE_SEND_ACK_ERROR: {
            char message[250]; // performance check
            sprintf(message, "Slave acknowledge error while sending data");
            jniController.throwANewJNIException(env, message);
            return I2C_EXCEPTION_OCCURRED;
        }
        case I2C_SLAVE_SEND_CLOCK_TIMEOUT_ERROR: {
            char message[250]; // performance check
            sprintf(message, "Slave timeout error while sending data");
            jniController.throwANewJNIException(env, message);
            return I2C_EXCEPTION_OCCURRED;
        }
        case I2C_SLAVE_SEND_DATA_LOSS_ERROR: {
            char message[250]; // performance check
            sprintf(message, "Data loss while sending data");
            jniController.throwANewJNIException(env, message);
            return I2C_EXCEPTION_OCCURRED;
        }
        case I2C_SLAVE_RECEIVE_ACK_ERROR: {
            char message[250]; // performance check
            sprintf(message, "Slave acknowledge error while receiving data");
            jniController.throwANewJNIException(env, message);
            return I2C_EXCEPTION_OCCURRED;
        }
        case I2C_SLAVE_RECEIVE_CLOCK_TIMEOUT_ERROR: {
            char message[250]; // performance check
            sprintf(message, "Slave timeout error while receiving data");
            jniController.throwANewJNIException(env, message);
            return I2C_EXCEPTION_OCCURRED;
        }
        case I2C_SLAVE_RECEIVE_DATA_LOSS_ERROR: {
            char message[250]; // performance check
            sprintf(message, "Data loss while receiving data");
            jniController.throwANewJNIException(env, message);
            return I2C_EXCEPTION_OCCURRED;
        }
        default: {
            return I2C_SUCCESS;
        }
    }

}