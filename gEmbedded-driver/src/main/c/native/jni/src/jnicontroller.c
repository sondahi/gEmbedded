#include "jnicontroller.h"

JniController jniController;

static jclass RuntimeExceptionClass;
static jclass JNIExceptionClass;

static JNI_STATUS getConstantDigit_(JNIEnv *env, jobject enumClass, jint *digitToReturn) {

    char message[250];

    const register jclass toGetEnumClass = (*env)->GetObjectClass(env, enumClass);
    if(toGetEnumClass == NULL){
        sprintf(message, "Enum class could not be found");
        jniController.throwANewJNIException(env, message);
        return JNI_EXCEPTION_OCCURRED;
    }

    const char *methodNameToFind = "getDigit";
    const char *methodSignatureToFind = "()I";

    jmethodID methodIdToFind = (*env)->GetMethodID(env, toGetEnumClass, methodNameToFind, methodSignatureToFind);
    if(methodIdToFind == NULL){
        sprintf(message, "getDigit() method could not be found");
        jniController.throwANewJNIException(env, message);
        return JNI_EXCEPTION_OCCURRED;
    }

    *digitToReturn = (*env)->CallIntMethod(env, enumClass, methodIdToFind);

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

JNI_STATUS jniSetup(JNIEnv *env) {

    const register jclass runtimeExceptionClazz = (*env)->FindClass(env, "java/lang/RuntimeException");
    RuntimeExceptionClass = (*env)->NewGlobalRef(env, runtimeExceptionClazz);

    const register jclass jniExceptionClazz = (*env)->FindClass(env, "com/comert/gEmbedded/api/device/exception/JNIException");
    if(jniExceptionClazz == NULL){
        return JNI_CLASSPATH_ERROR;
    }

    JNIExceptionClass = (*env)->NewGlobalRef(env, jniExceptionClazz);

    jniController.getConstantDigit = getConstantDigit_;
    jniController.throwANewJNIException = throwANewJNIException_;

    return JNI_SUCCESS;

}

void jniShutdown(JNIEnv *env) {

    (*env)->DeleteGlobalRef(env, RuntimeExceptionClass);
    (*env)->DeleteGlobalRef(env, JNIExceptionClass);

}