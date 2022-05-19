#ifndef I2CMASTER_H
#define I2CMASTER_H

#include "common.h"
#include <jni.h>

typedef enum I2C_STATUS_ {
    I2C_SUCCESS,
    I2C_ERROR
} I2C_STATUS;

I2C_STATUS i2cMasterDriverSetup (JNIEnv *env);

I2C_STATUS i2cMasterDriverShutdown (JNIEnv *env);

#endif
