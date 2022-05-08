#include <jni.h>

#ifndef JNICONTROLLER_H
#define JNICONTROLLER_H

typedef enum JNI_STATUS_ {
    JNI_SUCCESS,
    JNI_EXCEPTION_OCCURRED,
    JNI_CLASSPATH_ERROR,
    JNI_POINTER_ERROR,
} JNI_STATUS;

typedef struct JniController_ {
    JNI_STATUS (*getConstantDigit)(JNIEnv *env, jobject enumClass, jstring methodName, jstring methodSignature, jint *digitToReturn);
    void (*throwANewJNIException)(JNIEnv *env, const char *message);
} JniController;

extern JniController jniController;

JNI_STATUS jniSetup(JNIEnv *env, const char *jniExceptionClass);
void jniShutdown(JNIEnv *env);

#endif