#include <CUnit/Basic.h>
#include "jvmtest.h"

void testCreateJVM (void) {
    const JVM_STATUS status = createJVM ();
    if (status != JVM_SUCCESS) {
        CU_FAIL_FATAL("JVM should have been created")
    }
}

void testGetJNIEnv(void ){

    JNIEnv *jniEnv = NULL;
    JVM_STATUS status = getJNIEnv(&jniEnv);
    if (status != JVM_SUCCESS) {
        CU_FAIL_FATAL("JNI environment should have been created")
    }

    const jclass jniExceptionClazz = (*jniEnv)->FindClass (jniEnv, "com/comert/gEmbedded/api/device/exception/JNIException");
    if (jniExceptionClazz == NULL) {
        jboolean exceptionCheck = (*jniEnv)->ExceptionCheck (jniEnv);
        if (exceptionCheck == JNI_TRUE) {
            (*jniEnv)->ExceptionDescribe (jniEnv);
            (*jniEnv)->ExceptionClear (jniEnv);
        }
        CU_FAIL_FATAL("JNIException class should have been found")
    }

    jint throwResult = (*jniEnv)->ThrowNew (jniEnv, jniExceptionClazz, "***");
    if (throwResult != JNI_OK) {
        CU_FAIL_FATAL("JNI Exception should have been thrown")
    } else {
        jboolean exceptionCheck = (*jniEnv)->ExceptionCheck (jniEnv);
        if (exceptionCheck == JNI_TRUE) {
            (*jniEnv)->ExceptionClear (jniEnv);
        } else {
            CU_FAIL_FATAL("JNI Exception should have been caught")
        }
    }
}

void testDestroyJVM (void) {

    JVM_STATUS status = destroyJVM ();
    if (status != JVM_SUCCESS) {
        CU_FAIL_FATAL("JVM should have been destroyed")
    }

}