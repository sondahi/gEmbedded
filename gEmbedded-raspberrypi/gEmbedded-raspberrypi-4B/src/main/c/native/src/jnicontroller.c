/**
 * @author Gökay Cömert
 */

#include "jnicontroller.h"

JniController jniController;

static jclass RuntimeExceptionClass;
static jclass JNIExceptionClass;

static JNI_STATUS getConstantDigit_(JNIEnv *env, jobject enumClass, const jstring methodName,
                                    const jstring methodSignature, jint *digitToReturn) {

    char message[250];

    const register jclass toGetEnumClass = (*env)->GetObjectClass(env, enumClass);
    if(toGetEnumClass == NULL){
        sprintf(message, "Enum class could not be found");
        jniController.throwANewJNIException(env, message);
        return JNI_EXCEPTION_OCCURRED;
    }

    const char *methodNameToFind = (*env)->GetStringUTFChars(env, methodName, JNI_FALSE);
    if(methodNameToFind == NULL){
        (*env)->ReleaseStringUTFChars(env, methodName, methodNameToFind);
        sprintf(message, "Enum method name could not be found");
        jniController.throwANewJNIException(env, message);
        return JNI_EXCEPTION_OCCURRED;
    }

    const char *methodSignatureToFind = (*env)->GetStringUTFChars(env, methodSignature, JNI_FALSE);
    if(methodSignatureToFind == NULL){
        (*env)->ReleaseStringUTFChars(env, methodName, methodNameToFind);
        (*env)->ReleaseStringUTFChars(env, methodName, methodSignatureToFind);
        sprintf(message, "Enum method signature could not be found");
        jniController.throwANewJNIException(env, message);
        return JNI_EXCEPTION_OCCURRED;
    }

    jmethodID methodIdToFind = (*env)->GetMethodID(env, toGetEnumClass, methodNameToFind, methodSignatureToFind);
    if(methodIdToFind == NULL){
        (*env)->ReleaseStringUTFChars(env, methodName, methodNameToFind);
        (*env)->ReleaseStringUTFChars(env, methodSignature, methodSignatureToFind);
        sprintf(message, "Enum method could not be called");
        jniController.throwANewJNIException(env,message);
        return JNI_EXCEPTION_OCCURRED;
    }

    *digitToReturn = (*env)->CallIntMethod(env, enumClass, methodIdToFind);

    (*env)->ReleaseStringUTFChars(env, methodName, methodNameToFind);
    (*env)->ReleaseStringUTFChars(env, methodSignature, methodSignatureToFind);

    return JNI_SUCCESS;

}

static inline void throwANewRuntimeException(JNIEnv *env) {

    const char *message = "JNIException could not be thrown";
    (*env)->ThrowNew(env, RuntimeExceptionClass, message);

}

static void throwANewJNIException_(JNIEnv *env, const char *message) {

    const register jint throwNewJNIException = (*env)->ThrowNew(env, JNIExceptionClass, message);
    if (throwNewJNIException != JNI_OK) {
        throwANewRuntimeException(env);
    }

}

JNI_STATUS jniSetup(JNIEnv *env, const char *jniExceptionClass) {

    const register jclass runtimeExceptionClazz = (*env)->FindClass(env, "java/lang/RuntimeException");
    RuntimeExceptionClass = (*env)->NewGlobalRef(env, runtimeExceptionClazz);

    const register jclass jniExceptionClazz = (*env)->FindClass(env, jniExceptionClass);
    if (jniExceptionClazz == NULL) {
        return JNI_CLASSPATH_ERROR;
    }

    JNIExceptionClass = (*env)->NewGlobalRef(env, jniExceptionClazz);
    if (JNIExceptionClass == NULL) {
        return JNI_POINTER_ERROR;
    }

    jniController.getConstantDigit = getConstantDigit_;
    jniController.throwANewJNIException = throwANewJNIException_;

    return JNI_SUCCESS;

}

void jniShutdown(JNIEnv *env) {

    (*env)->DeleteGlobalRef(env, RuntimeExceptionClass);
    (*env)->DeleteGlobalRef(env, JNIExceptionClass);

}