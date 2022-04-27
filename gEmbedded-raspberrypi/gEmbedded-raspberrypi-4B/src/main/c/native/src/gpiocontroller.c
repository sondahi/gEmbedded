/**
 * @author Gökay Cömert
 */

#include "com_comert_gEmbedded_pi_nativeinterface_GPIOController.h"
#include "gpiodriver.h"

#include "jnicontroller.h"

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_GPIOController_setPinFunction
(JNIEnv *env, const jclass GPIOController, jobject pin, jobject pinFunction, const jstring methodName,
 const jstring methodSignature){

    jint pinNumberToSet, pinFunctionToSet;

    const register JNI_STATUS  pinStatus = jniController.getConstantDigit(env, pin, methodName, methodSignature, &pinNumberToSet);
    if(pinStatus == JNI_EXCEPTION_OCCURRED){
        return;
    }

    const register JNI_STATUS pinFunctionStatus = jniController.getConstantDigit
            (env, pinFunction, methodName, methodSignature, &pinFunctionToSet);

    if(pinFunctionStatus == JNI_EXCEPTION_OCCURRED){
        return;
    }

    const register GPIO_STATUS gpioStatus = gpioDriver.setPinFunction(pinNumberToSet, pinFunctionToSet);

    const register GPIO_STATUS gpioExceptionStatus = gpioStatusCheck(env, gpioStatus);
    if (gpioExceptionStatus == GPIO_EXCEPTION_OCCURRED) {
        return;
    }

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_GPIOController_setPullUpDownStatus
(JNIEnv *env, const jclass GPIOController, jobject pin, jobject pullUpDownStatus, const jstring methodName,
 const jstring methodSignature){

    jint pinNumberToSet, pullUpDownStatusToSet;

    const register JNI_STATUS  pinStatus = jniController.getConstantDigit(env, pin, methodName, methodSignature, &pinNumberToSet);
    if(pinStatus == JNI_EXCEPTION_OCCURRED){
        return;
    }

    const register JNI_STATUS pullUpDownStatusStatus = jniController.getConstantDigit
            (env, pullUpDownStatus, methodName, methodSignature, &pullUpDownStatusToSet);
    if(pullUpDownStatusStatus == JNI_EXCEPTION_OCCURRED){
        return;
    }

    const register GPIO_STATUS gpioStatus = gpioDriver.setPUDStatus(pinNumberToSet, pullUpDownStatusToSet);

    const register GPIO_STATUS gpioExceptionStatus = gpioStatusCheck(env, gpioStatus);
    if (gpioExceptionStatus == GPIO_EXCEPTION_OCCURRED) {
        return;
    }

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_GPIOController_setEventDetectStatus
(JNIEnv *env, const jclass GPIOController, jobject pin, jobject eventDetectStatus, const jstring methodName,
 const jstring methodSignature, const jstring fileName){

    jint pinNumberToSet, eventDetectStatusToSet;

    const register JNI_STATUS pinStatus = jniController.getConstantDigit(env, pin, methodName, methodSignature, &pinNumberToSet);
    if(pinStatus == JNI_EXCEPTION_OCCURRED){
        return;
    }

    const register JNI_STATUS eventDetectStatusStatus = jniController.getConstantDigit
            (env, eventDetectStatus, methodName, methodSignature, &eventDetectStatusToSet);
    if(eventDetectStatusStatus == JNI_EXCEPTION_OCCURRED){
        return;
    }

    const char *gpioFileName = (*env)->GetStringUTFChars(env, fileName, JNI_FALSE);
    if(gpioFileName == NULL){
        char message[250];
        (*env)->ReleaseStringUTFChars(env, fileName, gpioFileName);
        sprintf(message, "Event detect status could not be setup");
        jniController.throwANewJNIException(env, message);
        return;
    }

    const register GPIO_STATUS gpioStatus = gpioDriver.setEventDetectStatus(pinNumberToSet, eventDetectStatusToSet, gpioFileName);

    const register GPIO_STATUS gpioExceptionStatus = gpioStatusCheck(env, gpioStatus);
    if (gpioExceptionStatus == GPIO_EXCEPTION_OCCURRED) {
        (*env)->ReleaseStringUTFChars(env, fileName, gpioFileName);
        return;
    }

    (*env)->ReleaseStringUTFChars(env, fileName, gpioFileName);

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_GPIOController_releaseGPIOThreadRecourse
(JNIEnv *env, const jclass GPIOController, const jint pinNumber) {

    gpioDriver.releaseGPIOThreadSource(pinNumber);

}

JNIEXPORT jboolean JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_GPIOController_isHigh
(JNIEnv *env, const jclass GPIOController, const jint registerSelector, const jint pinSet) {

    return gpioDriver.isHigh(registerSelector, pinSet);

}

JNIEXPORT jboolean JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_GPIOController_isLow
(JNIEnv *env, const jclass GPIOController, const jint registerSelector, const jint pinSet) {

    return gpioDriver.isLow(registerSelector, pinSet);

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_GPIOController_write
(JNIEnv *env, const jclass GPIOController, const jint registerSelector, const jint pinSet) {

    gpioDriver.write(registerSelector, pinSet);

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_GPIOController_clear
(JNIEnv *env, const jclass GPIOController, const jint registerSelector, const jint pinSet) {

    gpioDriver.clear(registerSelector, pinSet);

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_GPIOController_pulse
(JNIEnv *env, const jclass GPIOController, const jint registerSelector, const jint pinSet, const jint highSleepTimeInMicSec,
 const jint lowSleepTimeInMicSec) {

    gpioDriver.pulse(registerSelector, pinSet, highSleepTimeInMicSec, lowSleepTimeInMicSec);

}

JNIEXPORT jint JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_GPIOController_poll
(JNIEnv *env, const jclass GPIOController, const jint pinNumber, const jint timeoutInMilSec) {

    return gpioDriver.poll(pinNumber, timeoutInMilSec);

}
