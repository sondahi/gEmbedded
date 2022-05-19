#include "com_comert_gEmbedded_nativeinterface_I2CMasterController.h"
#include "i2cmaster.h"
#include "jninative.h"
#include "mapper.h"

#define BSC0_BASE_ADDRESS       (PERIPHERAL_BASE_ADDRESS + 0x205000)
#define BSC1_BASE_ADDRESS       (PERIPHERAL_BASE_ADDRESS + 0x804000)
#define BSC_BLOCK_SIZE          (0x20)

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

BSCRegs *bscRegs[2];

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

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_nativeinterface_I2CMasterController_setMaster
        (JNIEnv *env, const jclass I2CMasterController, jobject bus, const jint busClockInHertz,
         const jint busClockStretchTimeout) {

    jint busSelector;

    const register JNI_STATUS busStatus = jniController.getEnumDigit (env, bus, &busSelector);
    if (busStatus == JNI_ERROR) {
        return;
    }

    const register reg_t divider = (CORE_CLOCK_SPEED / busClockInHertz);
    bscRegs[busSelector]->DIV = divider;
    bscRegs[busSelector]->CLKT = busClockStretchTimeout;

}

JNIEXPORT jint JNICALL Java_com_comert_gEmbedded_nativeinterface_I2CMasterController_getRegisterSelector
        (JNIEnv *env, jclass I2CMasterController, jobject bus) {

    jint busNumber;

    const register JNI_STATUS busStatus = jniController.getEnumDigit (env, bus, &busNumber);
    if (busStatus == JNI_ERROR) {
        return -1;
    }

    return busNumber;

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_nativeinterface_I2CMasterController_sendData
        (JNIEnv *env, const jclass I2CMasterController, const jint busSelector, const jbyte slaveAddress,
         const jbyteArray dataToSend, const jint dataToSendSize) {

    u8 buffer[16];
    (*env)->GetByteArrayRegion (env, dataToSend, 0, dataToSendSize, (jbyte *) buffer);

    bscRegs[busSelector]->A = (u8) slaveAddress;
    bscRegs[busSelector]->DLEN = dataToSendSize;
    bscRegs[busSelector]->S = S_CLEAR;
    bscRegs[busSelector]->C = C_SEND;

    register int count = 0;

    while (!(bscRegs[busSelector]->S & S_DONE)) {
        while (count < dataToSendSize && bscRegs[busSelector]->S & S_TXD) {
            bscRegs[busSelector]->FIFO = buffer[count++];
        }
    }

    const register reg_t status = bscRegs[busSelector]->S;
    if (status & S_ERR) {
        jniController.throwANewJNIException (env, "Slave acknowledge error while sending data");
        return;
    } else if (status & S_CLKT) {
        jniController.throwANewJNIException (env, "Slave timeout error while sending data");
        return;
    } else if (count < dataToSendSize) {
        jniController.throwANewJNIException (env, "Data loss while sending data");
        return;
    }

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_nativeinterface_I2CMasterController_receiveData
        (JNIEnv *env, const jclass I2CMasterController, const jint busSelector, const jbyte slaveAddress,
         const jintArray dataToReceive, const jint dataToReceiveSize) {

    bscRegs[busSelector]->A = (u8) slaveAddress;
    bscRegs[busSelector]->DLEN = dataToReceiveSize;
    bscRegs[busSelector]->S = S_CLEAR;
    bscRegs[busSelector]->C = C_RECEIVE;

    u32 buffer[16];

    register int count = 0;

    while (!(bscRegs[busSelector]->S & S_DONE)) {
        while (bscRegs[busSelector]->S & S_RXD) {
            buffer[count++] = bscRegs[busSelector]->FIFO & 0xFF;
        }
    }

    const register reg_t status = bscRegs[busSelector]->S;
    if (status & S_ERR) {
        jniController.throwANewJNIException (env, "Slave acknowledge error while reading data");
        return;
    } else if (status & S_CLKT) {
        jniController.throwANewJNIException (env, "Slave timeout error while reading data");
        return;
    } else if (count < dataToReceiveSize) {
        jniController.throwANewJNIException (env, "Data loss while reading data");
        return;
    }

    (*env)->SetIntArrayRegion (env, dataToReceive, 0, dataToReceiveSize, (jint *) buffer);

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_nativeinterface_I2CMasterController_sendAndReceiveData
        (JNIEnv *env, const jclass I2CMasterController, const jint busSelector, const jbyte slaveAddress,
         const jbyteArray dataToSend, const jint dataToSendSize, const jbyteArray dataToReceive,
         const jint dataToReceiveSize) {

    u8 bufferToSend[16];
    (*env)->GetByteArrayRegion (env, dataToSend, 0, dataToSendSize, (jbyte *) bufferToSend);

    bscRegs[busSelector]->A = (u8) slaveAddress;
    bscRegs[busSelector]->DLEN = dataToSendSize;
    bscRegs[busSelector]->S = S_CLEAR;
    bscRegs[busSelector]->C = C_SEND;

    register int count = 0;

    while (!(bscRegs[busSelector]->S & S_DONE)) {
        while (count < dataToSendSize && bscRegs[busSelector]->S & S_TXD) {
            bscRegs[busSelector]->FIFO = bufferToSend[count++];
        }
    }

    register reg_t status = bscRegs[busSelector]->S;
    if (status & S_ERR) {
        jniController.throwANewJNIException (env, "Slave acknowledge error while sending data");
        return;
    } else if (status & S_CLKT) {
        jniController.throwANewJNIException (env, "Slave timeout error while sending data");
        return;
    } else if (count < dataToSendSize) {
        jniController.throwANewJNIException (env, "Data loss while sending data");
        return;
    }

    bscRegs[busSelector]->DLEN = dataToReceiveSize;
    bscRegs[busSelector]->S = S_CLEAR;
    bscRegs[busSelector]->C = C_RECEIVE;

    u32 bufferToReturn[16];

    count = 0;

    while (!(bscRegs[busSelector]->S & S_DONE)) {
        while (bscRegs[busSelector]->S & S_RXD) {
            bufferToReturn[count++] = bscRegs[busSelector]->FIFO & 0xFF;
        }
    }

    status = bscRegs[busSelector]->S;
    if (status & S_ERR) {
        jniController.throwANewJNIException (env, "Slave acknowledge error while reading data");
        return;
    } else if (status & S_CLKT) {
        jniController.throwANewJNIException (env, "Slave timeout error while reading data");
        return;
    } else if (count < dataToReceiveSize) {
        jniController.throwANewJNIException (env, "Data loss while reading data");
        return;
    }

    (*env)->SetIntArrayRegion (env, dataToReceive, 0, dataToReceiveSize, (jint *) bufferToReturn);

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_nativeinterface_I2CMasterController_writeRegister
        (JNIEnv *env, const jclass I2CMasterController, const jint busSelector, const jbyte slaveAddress,
         const jbyte registerAddress, const jbyte dataToSend) {

    /*
    struct MessageToSend sMessage;
    sMessage.busSelector = busSelector;
    sMessage.address = slaveAddress;
    sMessage.dataToSend[0] = registerAddress;
    sMessage.dataToSend[1] = dataToSend;
    sMessage.dataToSendSize = 2;
     */

}

JNIEXPORT jint JNICALL Java_com_comert_gEmbedded_nativeinterface_I2CMasterController_readRegister
        (JNIEnv *env, const jclass I2CMasterController, const jint busSelector, const jbyte slaveAddress,
         const jbyte registerAddress) {

    /*
    struct MessageToSendAndReceive srMessage;
    srMessage.busSelector = busSelector;
    srMessage.address = slaveAddress;
    srMessage.dataToSend[0] = registerAddress;
    srMessage.dataToSendSize = 1;
    srMessage.dataToReceiveSize = 1;


    return (jint) srMessage.dataToReceive[0];
     */
    return 0;
}

JNIEXPORT jint JNICALL Java_com_comert_gEmbedded_nativeinterface_I2CMasterController_writeAndReadRegister
        (JNIEnv *env, const jclass I2CMasterController, const jint busSelector, const jbyte slaveAddress,
         const jbyte registerAddress, const jbyte dataToSend) {
/*
    struct MessageToSendAndReceive srMessage;
    srMessage.busSelector = busSelector;
    srMessage.address = slaveAddress;
    srMessage.dataToSend[0] = registerAddress;
    srMessage.dataToSend[1] = dataToSend;
    srMessage.dataToSendSize = 2;
    srMessage.dataToReceiveSize = 1;


    return (jint) srMessage.dataToReceive[0];
    */

    return 0;

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_nativeinterface_I2CMasterController_write
        (JNIEnv *env, const jclass I2CMasterController, const jint busSelector, const jbyte slaveAddress,
         const jbyte dataToSend) {
/*
    struct MessageToSend sMessage;
    sMessage.busSelector = busSelector;
    sMessage.address = slaveAddress;
    sMessage.dataToSend[0] = dataToSend;
    sMessage.dataToSendSize = 1;
    */


}

JNIEXPORT jint JNICALL Java_com_comert_gEmbedded_nativeinterface_I2CMasterController_read
        (JNIEnv *env, const jclass I2CMasterController, const jint busSelector, const jbyte slaveAddress) {

    /*
    struct MessageToReceive rMessage;
    rMessage.busSelector = busSelector;
    rMessage.address = slaveAddress;
    rMessage.dataToReceiveSize = 1;


    return (jint) rMessage.dataToReceive[0];
     */
    return 0;

}

I2C_STATUS i2cMasterDriverSetup (JNIEnv *env) {

    void *pointer;
    register MAPPER_STATUS mapperStatus;

    mapperStatus = mapBaseRegister (MEMORY_FILE_NAME, BSC_BLOCK_SIZE, BSC0_BASE_ADDRESS, &pointer);
    if (mapperStatus == MAPPER_ERROR) {
        jniController.throwANewJNIException (env, "/dev/mem could not be opened");
        return I2C_ERROR;
    } else if (mapperStatus == MAPPER_ERROR) {
        jniController.throwANewJNIException (env, "I2C memory mapping could not be setup");
        return I2C_ERROR;
    } else {
        bscRegs[0] = (BSCRegs *) pointer;
    }

    mapperStatus = mapBaseRegister (MEMORY_FILE_NAME, BSC_BLOCK_SIZE, BSC1_BASE_ADDRESS, &pointer);
    if (mapperStatus == MAPPER_ERROR) {
        return I2C_ERROR;
    } else if (mapperStatus == MAPPER_ERROR) {
        return I2C_ERROR;
    } else {
        bscRegs[1] = (BSCRegs *) pointer;
    }


    return I2C_SUCCESS;

}

I2C_STATUS i2cMasterDriverShutdown (JNIEnv *env) {

    bscRegs[0]->C = C_I2C_DIS;
    bscRegs[1]->C = C_I2C_DIS;

    BSCRegs *registers;

    registers = bscRegs[0];

    register MAPPER_STATUS mapperStatus = unmapBaseRegister ((void *) registers, BSC_BLOCK_SIZE);
    if (mapperStatus == MAPPER_ERROR) {
        jniController.throwANewJNIException (env, "I2C memory unmapping could not be setup");
        return I2C_ERROR;
    }

    registers = bscRegs[1];

    mapperStatus = unmapBaseRegister ((void *) registers, BSC_BLOCK_SIZE);
    if (mapperStatus == MAPPER_ERROR) {
        jniController.throwANewJNIException (env, "I2C memory unmapping could not be setup");
        return I2C_ERROR;
    }

    return I2C_SUCCESS;

}