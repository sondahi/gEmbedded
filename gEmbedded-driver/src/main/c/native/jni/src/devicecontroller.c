#include "com_comert_gEmbedded_nativeinterface_DeviceController.h"
#include "jnicontroller.h"
#include "gpiodriver.h"
#include "i2cmasterdriver.h"

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_nativeinterface_DeviceController_setupDevice
        (JNIEnv *env, jclass DeviceController){

    const register JNI_STATUS jniStatus = jniSetup (env);
    if(jniStatus != JNI_SUCCESS){
        const register jclass runtimeExceptionClazz = (*env)->FindClass(env, "java/lang/RuntimeException");
        const char *message = "JNI setup failed";
        (*env)->ThrowNew(env, runtimeExceptionClazz, message);
        return;
    }

    const register GPIO_STATUS gpioStatus = gpioDriverSetup();
    const register GPIO_STATUS gpioExceptionStatus = gpioStatusCheck (env, gpioStatus);
    if (gpioExceptionStatus == GPIO_EXCEPTION_OCCURRED) {
        return;
    }

    const register I2C_STATUS i2CStatus = i2cMasterDriverSetup ();
    const register I2C_STATUS i2cExceptionStatus = i2cStatusCheck (env, i2CStatus);
    if (i2cExceptionStatus == I2C_EXCEPTION_OCCURRED) {
        return;
    }

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_nativeinterface_DeviceController_shutdownDevice
        (JNIEnv *env, jclass DeviceController){

    const register I2C_STATUS i2CStatus = i2cMasterDriverShutdown ();
    const register I2C_STATUS i2cExceptionStatus = i2cStatusCheck (env, i2CStatus);
    if (i2cExceptionStatus == I2C_EXCEPTION_OCCURRED) {
        return;
    }

    const register GPIO_STATUS gpioStatus = gpioDriverShutdown ();
    const register GPIO_STATUS gpioExceptionStatus = gpioStatusCheck (env, gpioStatus);
    if (gpioExceptionStatus == GPIO_EXCEPTION_OCCURRED) {
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