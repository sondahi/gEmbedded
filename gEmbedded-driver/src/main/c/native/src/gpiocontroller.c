#include "com_comert_gEmbedded_nativeinterface_GPIOController.h"
#include "gpiodriver.h"
#include "jnicontroller.h"

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIOController_setPinFunction
        (JNIEnv *env, const jclass GPIOController, jobject pin, jobject pinFunction) {

    jint pinNumberToSet, pinFunctionToSet;

    const register JNI_STATUS pinStatus = jniController.getEnumDigit (env, pin, &pinNumberToSet);
    if (pinStatus == JNI_EXCEPTION_OCCURRED) {
        return;
    }

    const register JNI_STATUS pinFunctionStatus = jniController.getEnumDigit
            (env, pinFunction, &pinFunctionToSet);

    if (pinFunctionStatus == JNI_EXCEPTION_OCCURRED) {
        return;
    }

    const register GPIO_STATUS gpioStatus = gpioDriver.setPinFunction (pinNumberToSet, pinFunctionToSet);

    const register GPIO_STATUS gpioExceptionStatus = gpioStatusCheck (env, gpioStatus);
    if (gpioExceptionStatus == GPIO_EXCEPTION_OCCURRED) {
        return;
    }

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIOController_setPullUpDownStatus
        (JNIEnv *env, const jclass GPIOController, jobject pin, jobject pullUpDownStatus) {

    jint pinNumberToSet, pullUpDownStatusToSet;

    const register JNI_STATUS pinStatus = jniController.getEnumDigit (env, pin, &pinNumberToSet);
    if (pinStatus == JNI_EXCEPTION_OCCURRED) {
        return;
    }

    const register JNI_STATUS pullUpDownStatusStatus = jniController.getEnumDigit
            (env, pullUpDownStatus, &pullUpDownStatusToSet);
    if (pullUpDownStatusStatus == JNI_EXCEPTION_OCCURRED) {
        return;
    }

    const register GPIO_STATUS gpioStatus = gpioDriver.setPUDStatus (pinNumberToSet, pullUpDownStatusToSet);

    const register GPIO_STATUS gpioExceptionStatus = gpioStatusCheck (env, gpioStatus);
    if (gpioExceptionStatus == GPIO_EXCEPTION_OCCURRED) {
        return;
    }

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIOController_setEventDetectStatus
        (JNIEnv *env, const jclass GPIOController, jobject pin, jobject eventDetectStatus) {

    jint pinNumberToSet, eventDetectStatusToSet;

    const register JNI_STATUS pinStatus = jniController.getEnumDigit (env, pin, &pinNumberToSet);
    if (pinStatus == JNI_EXCEPTION_OCCURRED) {
        return;
    }

    const register JNI_STATUS eventDetectStatusStatus = jniController.getEnumDigit
            (env, eventDetectStatus, &eventDetectStatusToSet);
    if (eventDetectStatusStatus == JNI_EXCEPTION_OCCURRED) {
        return;
    }

    const char *gpioFileName = "/dev/gpiochip0";

    const register GPIO_STATUS gpioStatus = gpioDriver.setEventDetectStatus (pinNumberToSet, eventDetectStatusToSet,
                                                                             gpioFileName);

    const register GPIO_STATUS gpioExceptionStatus = gpioStatusCheck (env, gpioStatus);
    if (gpioExceptionStatus == GPIO_EXCEPTION_OCCURRED) {
        return;
    }

}

JNIEXPORT jint JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIOController_getRegisterSelector
        (JNIEnv *env, jclass GPIOController, jobject pin){

    jint pinNumber, registerSelector;

    const register JNI_STATUS pinStatus = jniController.getEnumDigit (env, pin, &pinNumber);
    if (pinStatus == JNI_EXCEPTION_OCCURRED) {
        return 0;
    }

    registerSelector = gpioDriver.getRegisterSelector(pinNumber);

    return registerSelector;
}

JNIEXPORT jint JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIOController_getPinSet
        (JNIEnv *env, jclass GPIOController, jobject pin){

    jint pinNumber, pinSet;

    const register JNI_STATUS pinStatus = jniController.getEnumDigit (env, pin, &pinNumber);
    if (pinStatus == JNI_EXCEPTION_OCCURRED) {
        return 0;
    }

    pinSet = gpioDriver.getPinset(pinNumber);

    return pinSet;

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIOController_releaseGPIOThreadRecourse
        (JNIEnv *env, const jclass GPIOController, const jint pinNumber) {

    gpioDriver.releaseGPIOThreadSource (pinNumber);

}

JNIEXPORT jboolean JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIOController_isHigh
        (JNIEnv *env, const jclass GPIOController, const jint registerSelector, const jint pinSet) {

    return gpioDriver.isHigh (registerSelector, pinSet);

}

JNIEXPORT jboolean JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIOController_isLow
        (JNIEnv *env, const jclass GPIOController, const jint registerSelector, const jint pinSet) {

    return gpioDriver.isLow (registerSelector, pinSet);

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIOController_write
        (JNIEnv *env, const jclass GPIOController, const jint registerSelector, const jint pinSet) {

    gpioDriver.write (registerSelector, pinSet);

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIOController_clear
        (JNIEnv *env, const jclass GPIOController, const jint registerSelector, const jint pinSet) {

    gpioDriver.clear (registerSelector, pinSet);

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIOController_pulse
        (JNIEnv *env, const jclass GPIOController, const jint registerSelector, const jint pinSet,
         const jint highSleepTimeInMicSec,
         const jint lowSleepTimeInMicSec) {

    gpioDriver.pulse (registerSelector, pinSet, highSleepTimeInMicSec, lowSleepTimeInMicSec);

}

JNIEXPORT jint JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIOController_poll
        (JNIEnv *env, const jclass GPIOController, const jint pinNumber, const jint timeoutInMilSec) {

    return gpioDriver.poll (pinNumber, timeoutInMilSec);

}
