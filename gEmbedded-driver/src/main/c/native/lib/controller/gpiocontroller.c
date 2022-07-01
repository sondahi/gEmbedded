#include "com_comert_gEmbedded_nativeinterface_GPIOController.h"
#include "gpiodriver.h"

JNIEXPORT jint JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIODriver_calculate1bitRegisterSelector
        (JNIEnv *env, jclass GPIOController, jobject pin){

    return 0;
}

JNIEXPORT jint JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIODriver_calculate1bitPinSet
        (JNIEnv *env, jclass GPIOController, jobject pin){

    return 0;
}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIODriver_setPinFunction
        (JNIEnv *env, jclass GPIOController, jobject pin, jobject pinFunction){

}

JNIEXPORT jobject JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIODriver_readPinFunction
        (JNIEnv *env, jclass GPIOController, jobject pin){

    return NULL;
}


JNIEXPORT void JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIODriver_setPullUpDownStatus
        (JNIEnv *env, jclass GPIOController, jobject pin, jobject pullUpDownStatus){

}

JNIEXPORT jobject JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIODriver_readPullUpDownStatus
        (JNIEnv *env, jclass GPIOController, jobject pin){

    return NULL;
}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIODriver_setEventDetectStatus
        (JNIEnv *env, jclass GPIOController, jobject pin, jobject eventDetectStatus){

}

JNIEXPORT jobject JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIODriver_readEventDetectStatus
        (JNIEnv *env, jclass GPIOController, jobject pin){

    return NULL;
}

JNIEXPORT jboolean JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIODriver_isPinHigh
        (JNIEnv *env, jclass GPIOController, jint registerSelector, jint pinSet){

    return JNI_FALSE;
}

JNIEXPORT jboolean JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIODriver_isPinLow
        (JNIEnv *env, jclass GPIOController, jint registerSelector, jint pinSet){

    return JNI_FALSE;
}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIODriver_writePin
        (JNIEnv *env, jclass GPIOController, jint registerSelector, jint pinSet){


}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIODriver_writePinFaster
        (JNIEnv *env, jclass GPIOController, jint registerSelector, jint pinSet){


}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIODriver_clearPin
        (JNIEnv *env, jclass GPIOController, jint registerSelector, jint pinSet){


}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIODriver_clearPinFaster
        (JNIEnv *env, jclass GPIOController, jint registerSelector, jint pinSet){


}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIODriver_pulsePin
        (JNIEnv *env, jclass GPIOController, jint registerSelector, jint pinSet, jint highSleepTimeInMicSec, jint lowSleepTimeInMicSec){


}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIODriver_pulsePinFaster
        (JNIEnv *env, jclass GPIOController, jint registerSelector, jint pinSet, jint highSleepTimeInMicSec, jint lowSleepTimeInMicSec){


}

JNIEXPORT jint JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIODriver_pollEvent
        (JNIEnv *env, jclass GPIOController, jint pinNumber, jint timeoutInMilSec){

    return 0;
}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIODriver_releaseGPIOThreadRecourse
        (JNIEnv *env, jclass GPIOController, jint pinNumber){

}