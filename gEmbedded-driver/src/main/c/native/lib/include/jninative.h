#include <jni.h>

#ifndef JNINATIVE_H
#define JNINATIVE_H

#define LARGEST_NUMBER_WORD (25)

typedef enum JNI_STATUS_ {
    JNI_SUCCESS,
    JNI_ERROR
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