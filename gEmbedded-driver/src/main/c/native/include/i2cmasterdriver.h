#ifndef I2CMASTERDRIVER_H
#define I2CMASTERDRIVER_H

#include "common.h"
#include <jni.h>

typedef enum I2C_STATUS_ {
    I2C_SUCCESS,
    I2C_EXCEPTION_OCCURRED,
    I2C_UNSUPPORTED_BUS_ERROR,
    I2C_BUS_DEV_FILE_OPEN_ERROR,
    I2C_BUS_MEM_MAP_ERROR,
    I2C_BUS_MEM_UNMAP_ERROR,
    I2C_BUS_DIV_ERROR,
    I2C_BUS_CLKT_ERROR,
    I2C_SLAVE_SEND_ACK_ERROR,
    I2C_SLAVE_SEND_CLOCK_TIMEOUT_ERROR,
    I2C_SLAVE_SEND_DATA_LOSS_ERROR,
    I2C_SLAVE_RECEIVE_ACK_ERROR,
    I2C_SLAVE_RECEIVE_CLOCK_TIMEOUT_ERROR,
    I2C_SLAVE_RECEIVE_DATA_LOSS_ERROR
} I2C_STATUS;

struct MessageToSend {
    jint busSelector;
    u8 address;
    u8 dataToSend[16];
    jint dataToSendSize;
};

struct MessageToReceive {
    jint busSelector;
    u8 address;
    reg_t dataToReceive[16];
    jint dataToReceiveSize;
};

struct MessageToSendAndReceive {
    jint busSelector;
    u8 address;
    u8 dataToSend[16];
    jint dataToSendSize;
    reg_t dataToReceive[16];
    jint dataToReceiveSize;
};

typedef struct I2CMaster_ {
    I2C_STATUS (*configure)(jint busSelector, jint busClockInHertz, jint busClockStretchTimeout);
    jint (*getRegisterSelector) (jint busNumber);
    I2C_STATUS (*sendData)(struct MessageToSend *sMessage);
    I2C_STATUS (*receiveData)(struct MessageToReceive *rMessage);
    I2C_STATUS (*sendAndReceiveData)(struct MessageToSendAndReceive *srMessage);
} I2CMaster;

extern I2CMaster i2CMasterDriver;

I2C_STATUS i2cMasterDriverSetup();
I2C_STATUS i2cMasterDriverShutdown();
I2C_STATUS i2cStatusCheck (JNIEnv *, I2C_STATUS);

#endif
