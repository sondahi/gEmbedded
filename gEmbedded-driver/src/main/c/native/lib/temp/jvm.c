#include <unistd.h>
#include <stdio.h>
#include "jvm.h"

static JavaVM *javaVm = NULL;
static JNIEnv *jniEnv = NULL;

JVM_STATUS createJVM () {

    JavaVMOption javaVmOption[1];
    javaVmOption[0].optionString = "-Djava.class.path=/usr/lib/java:../../../jni";

    JavaVMInitArgs javaVmInitArgs;
    javaVmInitArgs.version = JNI_VERSION_10;
    javaVmInitArgs.nOptions = 1;
    javaVmInitArgs.options = javaVmOption;
    javaVmInitArgs.ignoreUnrecognized = JNI_FALSE;

    jint result = JNI_CreateJavaVM (&javaVm, (void **) &jniEnv, &javaVmInitArgs);

    if (result != JNI_OK) {
        printf ("JVM could not be created. Error code : %d\n", result);
        return JVM_UNSUCCESS;
    }

    return JVM_SUCCESS;
}

JVM_STATUS getJNIEnv (JNIEnv **pJniEnv) {

    *pJniEnv = jniEnv;
    if (*pJniEnv == NULL) {
        printf ("JVM environment could not be initiated");
        return JVM_UNSUCCESS;
    }

    return JVM_SUCCESS;

}


JVM_STATUS destroyJVM () {

    if (javaVm == NULL) {
        printf ("JVM could not be destroyed. NULL pointer JavaVm");
        return JVM_UNSUCCESS;
    } else {
        jint result = (*javaVm)->DestroyJavaVM (javaVm);
        if (result != JNI_OK) {
            printf ("JVM could not be destroyed. Error code : %d\n", result);
            return JVM_UNSUCCESS;
        }
    }

    return JVM_SUCCESS;
}