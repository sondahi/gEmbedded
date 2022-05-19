#include "com_comert_gEmbedded_nativeinterface_DeviceController.h"
#include "jninative.h"
#include "gpio.h"
#include "i2cmaster.h"

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_nativeinterface_DeviceController_setupDevice
        (JNIEnv *env, jclass DeviceController){

    const register JNI_STATUS jniStatus = jniSetup (env);
    if(jniStatus != JNI_SUCCESS){
        const register jclass runtimeExceptionClazz = (*env)->FindClass(env, "java/lang/RuntimeException");
        const char *message = "JNI setup failed";
        (*env)->ThrowNew(env, runtimeExceptionClazz, message);
        return;
    }

    const register GPIO_STATUS gpioStatus = gpioDriverSetup(env);
    if (gpioStatus == GPIO_ERROR) {
        return;
    }

    const register I2C_STATUS i2CStatus = i2cMasterDriverSetup (env);
    if (i2CStatus == I2C_ERROR) {
        return;
    }

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_nativeinterface_DeviceController_shutdownDevice
        (JNIEnv *env, jclass DeviceController){

    const register I2C_STATUS i2CStatus = i2cMasterDriverShutdown (env);
    if (i2CStatus == I2C_ERROR) {
        return;
    }

    const register GPIO_STATUS gpioStatus = gpioDriverShutdown (env);
    if (gpioStatus == GPIO_ERROR) {
        return;
    }

    jniShutdown (env);
}

JNIEXPORT jobject JNICALL Java_com_comert_gEmbedded_nativeinterface_DeviceController_getNotSupportedPins
        (JNIEnv *env, jclass DeviceController){

    return NULL;
}

JNIEXPORT jobject JNICALL Java_com_comert_gEmbedded_nativeinterface_DeviceController_getNotSupportedI2CBusses
        (JNIEnv *env, jclass DeviceController){

    return NULL;
}