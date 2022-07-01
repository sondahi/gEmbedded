#include <CUnit/Basic.h>
#include "commontest.h"
#include "jvm.h"
#include "jninative.h"
#include "jninativetest.h"

#define TO_FIND_PIN         ("PIN_27")
#define TO_GET_PIN_DIGIT    (27)
#define TO_GET_PIN_TEXT     ("Twenty seven")


static JNIEnv *jniEnv = NULL;
static jobject pin = NULL;

int initJniControllerSuite (void) {

    if(getJNIEnv (&jniEnv)==JVM_UNSUCCESS){
        return SCENARIO_FAIL;
    }

    jclass pinClass = (*jniEnv)->FindClass (jniEnv, "com/comert/gEmbedded/api/device/gpio/pin/Pin");
    if (pinClass == NULL) {
        (*jniEnv)->ExceptionDescribe (jniEnv);
        (*jniEnv)->ExceptionClear (jniEnv);
        return SCENARIO_FAIL;
    } else {
        // GetStaticFieldID() causes an uninitialized class to be initialized.
        jfieldID pinId = (*jniEnv)->GetStaticFieldID (jniEnv, pinClass, TO_FIND_PIN,
                                                      "Lcom/comert/gEmbedded/api/device/gpio/pin/Pin;");
        if (pinId == NULL) {
            (*jniEnv)->ExceptionDescribe (jniEnv);
            (*jniEnv)->ExceptionClear (jniEnv);
            return SCENARIO_FAIL;
        } else {
            pin = (*jniEnv)->GetStaticObjectField (jniEnv, pinClass, pinId);
        }
    }

    if((*jniEnv)->ExceptionCheck(jniEnv)==JNI_TRUE){
        (*jniEnv)->ExceptionDescribe(jniEnv);
        (*jniEnv)->ExceptionClear(jniEnv);
        return SCENARIO_FAIL;
    }

    return SCENARIO_SUCCESS;
}

int cleanupJniControllerSuite (void) {
    jniEnv = NULL;
    pin = NULL;
    return SCENARIO_SUCCESS;
}

void testJniSetup (void) {
    JNI_STATUS status;
    status = jniSetup (NULL);
    CU_ASSERT_EQUAL_FATAL(status, JNI_ERROR)

    status = jniSetup (jniEnv);
    CU_ASSERT_EQUAL_FATAL(status, JNI_SUCCESS)

    // second setup fails
    status = jniSetup (jniEnv);
    CU_ASSERT_EQUAL_FATAL(status, JNI_ERROR)
}
void testGetEnumDigit (void) {
    jint intValue = -1;
    JNI_STATUS status;

    status = jniController.getEnumDigit (NULL, pin, &intValue);
    CU_ASSERT_EQUAL(status, JNI_ERROR)

    status = jniController.getEnumDigit (jniEnv, NULL, &intValue);
    CU_ASSERT_EQUAL(status, JNI_ERROR)

    status = jniController.getEnumDigit (jniEnv, pin, &intValue);
    CU_ASSERT_EQUAL(status, JNI_SUCCESS)
    CU_ASSERT_EQUAL(intValue, TO_GET_PIN_DIGIT)
}

void testGetEnumText (void) {
    JNI_STATUS status;

    char text[LARGEST_NUMBER_WORD];
    const jint textSize = sizeof (text);

    status = jniController.getEnumText (NULL, pin, text, textSize);
    CU_ASSERT_EQUAL(status, JNI_ERROR)

    status = jniController.getEnumText (jniEnv, NULL, text, textSize);
    CU_ASSERT_EQUAL(status, JNI_ERROR)

    status = jniController.getEnumText (jniEnv, pin, NULL, textSize);
    CU_ASSERT_EQUAL(status, JNI_ERROR)

    status = jniController.getEnumText (jniEnv, pin, text, LARGEST_NUMBER_WORD - 1);
    CU_ASSERT_EQUAL(status, JNI_ERROR)

    status = jniController.getEnumText (jniEnv, pin, text, LARGEST_NUMBER_WORD + 1);
    CU_ASSERT_EQUAL(status, JNI_ERROR)

    status = jniController.getEnumText (jniEnv, pin, text, textSize);
    CU_ASSERT_EQUAL(status, JNI_SUCCESS)
    CU_ASSERT_STRING_EQUAL(text, TO_GET_PIN_TEXT)

}

void testThrowANewJNIException (void) {

    //jniController.throwANewJNIException(NULL,"Hello World");
    //jniController.throwANewJNIException(jniEnv,NULL);

    jniController.throwANewJNIException (jniEnv, "***Test***");
    jboolean result = (*jniEnv)->ExceptionCheck (jniEnv);
    CU_ASSERT_EQUAL(result, JNI_TRUE)
    (*jniEnv)->ExceptionDescribe (jniEnv);
    (*jniEnv)->ExceptionClear (jniEnv);

    CU_ASSERT_EQUAL_FATAL((*jniEnv)->ExceptionCheck (jniEnv), JNI_FALSE)
}

void testJniShutdown (void) {
    JNI_STATUS status;

    status = jniShutdown (NULL);
    CU_ASSERT_EQUAL_FATAL(status, JNI_ERROR)

    status = jniShutdown (jniEnv);
    CU_ASSERT_EQUAL_FATAL(status, JNI_SUCCESS)

    // second shutdown fails
    status = jniShutdown (jniEnv);
    CU_ASSERT_EQUAL_FATAL(status, JNI_ERROR)
}
