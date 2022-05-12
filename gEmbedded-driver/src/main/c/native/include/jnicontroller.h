#include <jni.h>

#ifndef JNICONTROLLER_H
#define JNICONTROLLER_H

typedef enum JNI_STATUS_ {
    JNI_SUCCESS,
    JNI_EXCEPTION_OCCURRED,
    JNI_CLASSPATH_ERROR,
    JNI_GLOBAL_REFERENCE_ERROR,
    JNI_GET_ENUM_TEXT_SIZE_ERROR
} JNI_STATUS;

typedef struct JniController_ {
    JNI_STATUS (*getEnumDigit) (JNIEnv *env, jobject enumObject, jint *digitToReturn);

    JNI_STATUS (*getEnumText) (JNIEnv *env, jobject enumObject, char *textToReturn, int textToReturnSize);

    void (*throwANewJNIException) (JNIEnv *env, const char *message);
} JniController;

extern JniController jniController;

JNI_STATUS jniSetup (JNIEnv *env);

JNI_STATUS jniShutdown (JNIEnv *env);

#endif