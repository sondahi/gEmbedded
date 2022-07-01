#include <jni.h>

#ifndef JNICONTROLLER_H
#define JNICONTROLLER_H

#define LARGEST_NUMBER_WORD (25)

typedef enum JNI_STATUS_ {
    JNI_SUCCESS,
    JNI_ERROR
} JNI_STATUS;

JNI_STATUS getEnumDigit (JNIEnv *env, jobject enumObject, jint *digitToReturn);

JNI_STATUS getEnumText (JNIEnv *env, jobject enumObject, char *textToReturn, int textToReturnSize);

JNI_STATUS jniSetup (JNIEnv *env);

JNI_STATUS jniShutdown (JNIEnv *env);

#endif