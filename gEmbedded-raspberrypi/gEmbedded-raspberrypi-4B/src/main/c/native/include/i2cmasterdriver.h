/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   i2cmasterdriver.h
 * Author: Gökay Cömert
 *
 * Created on 17. April 2022, 22:29
 */
#include "i2cmasterexception.h"

#ifndef I2CMASTERDRIVER_H
#define I2CMASTERDRIVER_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include <jni.h>
#include "common.h"
#include "i2cmasterexception.h"
    
struct MessageToSend {
    jint busSelector;
    u8 address;
    u8 dataToSend[16];
    jint dataToSendSize;
};

struct MessageToReceive {
    jint busSelector;
    u8 address;
    u32 dataToReceive[16];
    jint dataToReceiveSize;
};

struct MessageToSendAndReceive {
    jint busSelector;
    u8 address;
    u8 dataToSend[16];
    jint dataToSendSize;
    u32 dataToReceive[16];
    jint dataToReceiveSize;
};

typedef struct I2CMaster_ {
    I2C_STATUS (*configure)(jint busSelector, jint busClockInHertz, jint busClockStretchTimeout);
    I2C_STATUS (*sendData)(struct MessageToSend *sMessage);
    I2C_STATUS (*receiveData)(struct MessageToReceive *rMessage);
    I2C_STATUS (*sendAndReceiveData)(struct MessageToSendAndReceive *srMessage);
} I2CMaster;

extern I2CMaster i2CMasterDriver;

I2C_STATUS i2cMasterDriverSetup(jint busSelector);
I2C_STATUS i2cMasterDriverShutdown(jint busSelector);

#ifdef __cplusplus
}
#endif

#endif /* I2CMASTERDRIVER_H */
