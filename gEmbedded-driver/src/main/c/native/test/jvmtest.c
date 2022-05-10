#include <CUnit/Basic.h>
#include "jvmtest.h"

static JavaVM *jvm;
static JNIEnv *env;

void testCreateJVM (void) {

    const JVM_STATUS status = createJVM (&jvm, &env);
    if (status != JVM_SUCCESSFUL) {
        CU_FAIL_FATAL("JVM should have been created")
    }

    const jclass jniExceptionClazz = (*env)->FindClass (env, "com/comert/gEmbedded/api/device/exception/JNIException");
    if (jniExceptionClazz == NULL) {
        jboolean exceptionCheck = (*env)->ExceptionCheck (env);
        if (exceptionCheck == JNI_TRUE) {
            (*env)->ExceptionDescribe (env);
            (*env)->ExceptionClear (env);
        }
        CU_FAIL_FATAL("JNIException class should have been found")
    }

    jint throwResult = (*env)->ThrowNew (env, jniExceptionClazz, "***");
    if (throwResult != JNI_OK) {
        CU_FAIL_FATAL("JNI Exception should have been thrown")
    } else {
        jboolean exceptionCheck = (*env)->ExceptionCheck (env);
        if (exceptionCheck == JNI_TRUE) {
            (*env)->ExceptionClear (env);
        } else {
            CU_FAIL_FATAL("JNI Exception should have been caught")
        }
    }
}

void testDestroyJVM (void) {

    JVM_STATUS status = destroyJVM (jvm);
    CU_ASSERT_EQUAL(status, JVM_SUCCESSFUL)

}