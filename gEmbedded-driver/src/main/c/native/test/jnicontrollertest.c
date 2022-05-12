#include <CUnit/Basic.h>
#include "commontest.h"
#include "jvm.h"
#include "jnicontrollertest.h"

static JNIEnv *jniEnv;
static jobject pinObject;

int initJniControllerSuite (void) {
    JVM_STATUS status = getJNIEnv (&jniEnv);
    if (status != JVM_SUCCESS) {
        return SCENARIO_FAIL;
    } else {
        jclass pinClass = (*jniEnv)->FindClass (jniEnv, "com/comert/gEmbedded/api/device/gpio/pin/Pin");
        if (pinClass == NULL) {
            printf ("Failed class");
            return SCENARIO_FAIL;
        } else {
            jfieldID pinId = (*jniEnv)->GetStaticFieldID (jniEnv, pinClass, "PIN_0",
                                                          "Lcom/comert/gEmbedded/api/device/gpio/pin/Pin;");
            if (pinId == NULL) {
                printf ("Failed jfieldID");
                return SCENARIO_FAIL;
            } else {
                pinObject = (*jniEnv)->GetStaticObjectField (jniEnv, pinClass, pinId);
                if (pinObject == NULL) {
                    printf ("Failed pinObject");
                    return SCENARIO_FAIL;
                }
                return SCENARIO_SUCCESS;
            }
        }
    }
}

int cleanupJniControllerSuite (void) {
    jniEnv = NULL;
    return SCENARIO_SUCCESS;
}

void testJniSetup (void) {
    JNI_STATUS status = jniSetup (jniEnv);
    CU_ASSERT_EQUAL_FATAL(status, JNI_SUCCESS)
}

void testGetConstantDigit (void) {
    jint intValue;
    JNI_STATUS status = jniController.getEnumDigit (jniEnv, pinObject, &intValue);
    CU_ASSERT_EQUAL(status, JNI_SUCCESS)
    CU_ASSERT_EQUAL(intValue, 0)
}

void testGetConstantText(void) {
    JNI_STATUS status;

    char invalidStringValue[1];
    status = jniController.getEnumText (jniEnv, pinObject, invalidStringValue, sizeof (invalidStringValue));
    CU_ASSERT_EQUAL(status,JNI_GET_ENUM_TEXT_SIZE_ERROR)

    char stringValue[10];
    status = jniController.getEnumText (jniEnv, pinObject, stringValue, sizeof (stringValue));
    (*jniEnv)->ExceptionDescribe(jniEnv);
    CU_ASSERT_EQUAL(status, JNI_SUCCESS)
    CU_ASSERT_STRING_EQUAL(stringValue, "Zero")
}

void testThrowANewJNIException (void) {
    char *message = "***TEST***";
    jniController.throwANewJNIException (jniEnv, message);
    jboolean result = (*jniEnv)->ExceptionCheck (jniEnv);
    CU_ASSERT_EQUAL_FATAL(result, JNI_TRUE)
    (*jniEnv)->ExceptionDescribe (jniEnv);
    (*jniEnv)->ExceptionClear (jniEnv);
}

void testJniShutdown (void) {
    JNI_STATUS status = jniShutdown (jniEnv);
    CU_ASSERT_EQUAL_FATAL(status, JNI_SUCCESS)
}
