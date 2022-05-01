#include "com_comert_gEmbedded_pi_nativeinterface_DeviceController.h"
#include "jnicontroller.h"
#include "gpiodriver.h"
#include "i2cmasterdriver.h"

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_DeviceController_setUpJNIDriver
        (JNIEnv *env, const jclass DeviceController, const jstring jniExceptionClass) {

    const register jclass runtimeException = (jclass) (*env)->FindClass (env, "java/lang/RuntimeException");

    const char *jniExceptionClazz = (*env)->GetStringUTFChars (env, jniExceptionClass, JNI_FALSE);
    if (jniExceptionClazz == NULL) {
        char message[250];
        sprintf (message, "JNIException class could not be pointed");
        (*env)->ThrowNew (env, runtimeException, message);
        (*env)->ReleaseStringUTFChars (env, jniExceptionClass, jniExceptionClazz);
        return;
    }

    const register JNI_STATUS javaStatus = jniSetup (env, jniExceptionClazz);
    if (javaStatus == JNI_CLASSPATH_ERROR) {
        char message[250];
        sprintf (message, "JNIException class could not be found in classpath");
        (*env)->ThrowNew (env, runtimeException, message);
        (*env)->ReleaseStringUTFChars (env, jniExceptionClass, jniExceptionClazz);
        return;
    }
    if (javaStatus == JNI_POINTER_ERROR) {
        char message[250];
        sprintf (message, "JNIException class could not be pointed");
        (*env)->ThrowNew (env, runtimeException, message);
        (*env)->ReleaseStringUTFChars (env, jniExceptionClass, jniExceptionClazz);
        return;
    }

    (*env)->ReleaseStringUTFChars (env, jniExceptionClass, jniExceptionClazz);

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_DeviceController_shutDownJNIDriver
        (JNIEnv *env, const jclass DeviceController) {

    jniShutdown (env);

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_DeviceController_setUpGpioDriver
        (JNIEnv *env, const jclass DeviceController) {

    const register GPIO_STATUS gpioStatus = gpioDriverSetup();

    const register GPIO_STATUS gpioExceptionStatus = gpioStatusCheck (env, gpioStatus);
    if (gpioExceptionStatus == GPIO_EXCEPTION_OCCURRED) {
        return;
    }
}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_DeviceController_shutDownGpioDriver
        (JNIEnv *env, const jclass DeviceController) {

    const register GPIO_STATUS gpioStatus = gpioDriverShutdown ();

    const register GPIO_STATUS gpioExceptionStatus = gpioStatusCheck (env, gpioStatus);
    if (gpioExceptionStatus == GPIO_EXCEPTION_OCCURRED) {
        return;
    }

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_DeviceController_setUpI2CMasterDriver
        (JNIEnv *env, const jclass DeviceController, const jint busNumber) {

    const register I2C_STATUS i2CStatus = i2cMasterDriverSetup (busNumber);

    const register I2C_STATUS i2cExceptionStatus = i2cStatusCheck (env, i2CStatus);
    if (i2cExceptionStatus == I2C_EXCEPTION_OCCURRED) {
        return;
    }
}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_DeviceController_shutDownI2CMasterDriver
        (JNIEnv *env, jclass DeviceController, const jint busNumber) {

    const register I2C_STATUS i2CStatus = i2cMasterDriverShutdown (busNumber);

    const register I2C_STATUS i2cExceptionStatus = i2cStatusCheck (env, i2CStatus);
    if (i2cExceptionStatus == I2C_EXCEPTION_OCCURRED) {
        return;
    }

}
