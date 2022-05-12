#include "jnicontroller.h"

JniController jniController;

static jclass RuntimeExceptionClass;
static jclass JNIExceptionClass;

static JNI_STATUS getEnumDigit_ (JNIEnv *env, jobject enumObject, jint *digitToReturn) {

    char message[250];

    const jclass toGetEnumClass = (*env)->GetObjectClass (env, enumObject);
    if (toGetEnumClass == NULL) {
        sprintf (message, "Enum class could not be found");
        jniController.throwANewJNIException (env, message);
        return JNI_EXCEPTION_OCCURRED;
    }

    const char *methodNameToFind = "getDigit";
    const char *methodSignatureToFind = "()I";

    jmethodID methodIdToFind = (*env)->GetMethodID (env, toGetEnumClass, methodNameToFind, methodSignatureToFind);
    if (methodIdToFind == NULL) {
        sprintf (message, "getDigit() method could not be found");
        jniController.throwANewJNIException (env, message);
        return JNI_EXCEPTION_OCCURRED;
    }

    *digitToReturn = (*env)->CallIntMethod (env, enumObject, methodIdToFind);

    return JNI_SUCCESS;

}

static JNI_STATUS getEnumText_ (JNIEnv *env, jobject enumObject, char *textToReturn, int textToReturnSize) {
    char message[250];

    const register jclass toGetEnumClass = (*env)->GetObjectClass (env, enumObject);
    if (toGetEnumClass == NULL) {
        sprintf (message, "Enum class could not be found");
        jniController.throwANewJNIException (env, message);
        return JNI_EXCEPTION_OCCURRED;
    }

    const char *methodNameToFind = "getText";
    const char *methodSignatureToFind = "()Ljava/lang/String;";

    jmethodID methodIdToFind = (*env)->GetMethodID (env, toGetEnumClass, methodNameToFind, methodSignatureToFind);
    if (methodIdToFind == NULL) {
        sprintf (message, "getText() method could not be found");
        jniController.throwANewJNIException (env, message);
        return JNI_EXCEPTION_OCCURRED;
    }

    jstring toGetTextString = (jstring) (*env)->CallObjectMethod (env, enumObject, methodIdToFind);
    jboolean isCopy = JNI_TRUE;
    const char *text = (*env)->GetStringUTFChars (env, toGetTextString, &isCopy);
    const size_t textSize = sizeof (text);
    if (textSize > textToReturnSize) {
        (*env)->ReleaseStringUTFChars (env, toGetTextString, text);
        return JNI_GET_ENUM_TEXT_SIZE_ERROR;
    } else {
        for (int i = 0; i <= textSize; ++i) {
            textToReturn[i] = text[i];
            if (i == textSize) {
                textToReturn[i] = '\0';
            }
        }
    }

    (*env)->ReleaseStringUTFChars (env, toGetTextString, text);

    return JNI_SUCCESS;
}

static inline void throwANewRuntimeException (JNIEnv *env) {

    const char *message = "JNIException could not be thrown";
    (*env)->ThrowNew (env, RuntimeExceptionClass, message);

}

static void throwANewJNIException_ (JNIEnv *env, const char *message) {

    const register jint throwNewJNIException = (*env)->ThrowNew (env, JNIExceptionClass, message);
    if (throwNewJNIException != JNI_OK) {
        throwANewRuntimeException (env);
    }

}

JNI_STATUS jniSetup (JNIEnv *env) {

    const jclass runtimeExceptionClazz = (*env)->FindClass (env, "java/lang/RuntimeException");
    if (runtimeExceptionClazz == NULL) {
        // exception occurred decide to clear or not
        return JNI_CLASSPATH_ERROR;
    }
    RuntimeExceptionClass = (*env)->NewGlobalRef (env, runtimeExceptionClazz);
    if (RuntimeExceptionClass == NULL) {
        return JNI_GLOBAL_REFERENCE_ERROR;
    }

    const register jclass jniExceptionClazz = (*env)->FindClass (env,
                                                                 "com/comert/gEmbedded/api/device/exception/JNIException");
    if (jniExceptionClazz == NULL) {
        return JNI_CLASSPATH_ERROR;
    }
    JNIExceptionClass = (*env)->NewGlobalRef (env, jniExceptionClazz);
    if (JNIExceptionClass == NULL) {
        return JNI_GLOBAL_REFERENCE_ERROR;
    }

    jniController.getEnumDigit = getEnumDigit_;
    jniController.getEnumText = getEnumText_;
    jniController.throwANewJNIException = throwANewJNIException_;

    return JNI_SUCCESS;

}

JNI_STATUS jniShutdown (JNIEnv *env) {

    (*env)->DeleteGlobalRef (env, RuntimeExceptionClass);
    (*env)->DeleteGlobalRef (env, JNIExceptionClass);

    return JNI_SUCCESS;

}