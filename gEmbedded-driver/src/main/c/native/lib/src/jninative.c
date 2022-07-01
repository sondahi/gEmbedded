#include <stdlib.h>
#include "jninative.h"

JniController jniController;

static jclass RuntimeExceptionClass = NULL;
static jclass JNIExceptionClass = NULL;

static JNI_STATUS getEnumDigit_ (JNIEnv *env, jobject enumObject, jint *digitToReturn) {

    if (env == NULL || enumObject == NULL) {
        return JNI_ERROR;
    }

    const jclass toGetEnumClass = (*env)->GetObjectClass (env, enumObject);
    const char *methodNameToFind = "getDigit";
    const char *methodSignatureToFind = "()I";

    jmethodID methodIdToFind = (*env)->GetMethodID (env, toGetEnumClass, methodNameToFind, methodSignatureToFind);
    if (methodIdToFind == NULL) {
        if ((*env)->ExceptionCheck (env) == JNI_TRUE) {
            (*env)->ExceptionDescribe (env);
            (*env)->ExceptionClear (env);
        }
        return JNI_ERROR;
    }

    *digitToReturn = (*env)->CallIntMethod (env, enumObject, methodIdToFind);
    if ((*env)->ExceptionCheck (env) == JNI_TRUE) {
        (*env)->ExceptionDescribe (env);
        (*env)->ExceptionClear (env);
        return JNI_ERROR;
    }

    return JNI_SUCCESS;

}

static JNI_STATUS getEnumText_ (JNIEnv *env, jobject enumObject, char *textToReturn, int textToReturnSize) {

    if (env == NULL || enumObject == NULL || textToReturn == NULL || textToReturnSize != LARGEST_NUMBER_WORD) {
        return JNI_ERROR;
    }

    const jclass toGetEnumClass = (*env)->GetObjectClass (env, enumObject);
    const char *methodNameToFind = "getText";
    const char *methodSignatureToFind = "()Ljava/lang/String;";

    jmethodID methodIdToFind = (*env)->GetMethodID (env, toGetEnumClass, methodNameToFind, methodSignatureToFind);
    if (methodIdToFind == NULL) {
        if ((*env)->ExceptionCheck (env) == JNI_TRUE) {
            (*env)->ExceptionDescribe (env);
            (*env)->ExceptionClear (env);
        }
        return JNI_ERROR;
    }

    jstring toGetString = (jstring) (*env)->CallObjectMethod (env, enumObject, methodIdToFind);
    if ((*env)->ExceptionCheck (env) == JNI_TRUE) {
        (*env)->ExceptionDescribe (env);
        (*env)->ExceptionClear (env);
        return JNI_ERROR;
    }

    const char *text = (*env)->GetStringUTFChars (env, toGetString, NULL);
    if (text == NULL) {
        return JNI_ERROR;
    }

    const jsize textSize = (*env)->GetStringUTFLength (env, toGetString);
    if (textSize >= LARGEST_NUMBER_WORD) {
        return JNI_ERROR;
    }

    for (int i = 0; i <= LARGEST_NUMBER_WORD; ++i) {
        textToReturn[i] = text[i];
        if (i == textSize) {
            textToReturn[i] = '\0';
            break;
        }
    }

    (*env)->ReleaseStringUTFChars (env, toGetString, text);

    return JNI_SUCCESS;
}

static void throwANewJNIException_ (JNIEnv *env, const char *message) {

    if (env == NULL || message == NULL) {
        printf ("FATAL ERROR : JNIException could not be thrown in native library. env or message is NULL");
        exit (EXIT_FAILURE);
    }

    const register jint throwNewJNIException = (*env)->ThrowNew (env, JNIExceptionClass, message);
    if (throwNewJNIException != JNI_OK) {
        const jint throwNewRuntimeException = (*env)->ThrowNew (env, RuntimeExceptionClass,
                                                                "JNIException could not be thrown");
        if (throwNewRuntimeException != JNI_OK) {
            printf ("RuntimeException could not be thrown in native library");
            exit (EXIT_FAILURE);
        }
    }

}

JNI_STATUS jniSetup (JNIEnv *env) {

    if (env == NULL || JNIExceptionClass != NULL || RuntimeExceptionClass != NULL) {
        return JNI_ERROR;
    }

    const jclass runtimeExceptionClazz = (*env)->FindClass (env, "java/lang/RuntimeException");
    if (runtimeExceptionClazz == NULL) {
        if ((*env)->ExceptionCheck (env) == JNI_TRUE) {
            (*env)->ExceptionDescribe (env);
            (*env)->ExceptionClear (env);
        }
        return JNI_ERROR;
    }
    RuntimeExceptionClass = (jclass) (*env)->NewGlobalRef (env, runtimeExceptionClazz);
    if (RuntimeExceptionClass == NULL) {
        return JNI_ERROR;
    }

    const jclass jniExceptionClazz = (*env)->FindClass (env,
                                                        "com/comert/gEmbedded/api/device/exception/JNIException");
    if (jniExceptionClazz == NULL) {
        if ((*env)->ExceptionCheck (env) == JNI_TRUE) {
            (*env)->ExceptionDescribe (env);
            (*env)->ExceptionClear (env);
        }
        return JNI_ERROR;
    }
    JNIExceptionClass = (*env)->NewGlobalRef (env, jniExceptionClazz);
    if (JNIExceptionClass == NULL) {
        return JNI_ERROR;
    }

    jniController.getEnumDigit = getEnumDigit_;
    jniController.getEnumText = getEnumText_;
    jniController.throwANewJNIException = throwANewJNIException_;

    return JNI_SUCCESS;

}

JNI_STATUS jniShutdown (JNIEnv *env) {

    if (env == NULL || RuntimeExceptionClass == NULL || JNIExceptionClass == NULL) {
        return JNI_ERROR;
    }

    (*env)->DeleteGlobalRef (env, RuntimeExceptionClass);
    (*env)->DeleteGlobalRef (env, JNIExceptionClass);

    RuntimeExceptionClass = NULL;
    JNIExceptionClass = NULL;


    return JNI_SUCCESS;
}