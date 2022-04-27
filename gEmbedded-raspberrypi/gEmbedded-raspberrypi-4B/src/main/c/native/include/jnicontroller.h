/**
 * @author Gökay Cömert
 */

#include <jni.h>

#ifndef NATIVE32_JNICONTROLLER_H
#define NATIVE32_JNICONTROLLER_H
#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif
#endif //NATIVE32_JNICONTROLLER_H