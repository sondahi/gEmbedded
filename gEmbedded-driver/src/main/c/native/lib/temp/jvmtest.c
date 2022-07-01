#include <CUnit/Basic.h>
#include "jvm.h"
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

    // test if jniEnv works
    const jint jre17Version = 655360;
    jint version = (*jniEnv)->GetVersion(jniEnv);
    CU_ASSERT_EQUAL_FATAL(version,jre17Version);

}

void testDestroyJVM (void) {

    JVM_STATUS status = destroyJVM ();
    if (status != JVM_SUCCESS) {
        CU_FAIL_FATAL("JVM should have been destroyed")
    }

}