#include <CUnit/Basic.h>
#include "commontest.h"

#include "com_comert_gEmbedded_nativeinterface_GPIOController.h"
#include "gpio.h"
#include "gpiotest.h"
#include "jvm.h"
#include "jninative.h"

static jint readerPin = 20;
static jint readerFunction = 6;
static jint readerRegisterSelector;
static jint readerPinSet;

static jint writerPin = 21;
static jint writerFunction = 7;
static jint writerRegisterSelector;
static jint writerPinSet;

#define READER_PIN          ("PIN_20")
#define WRITER_PIN          ("PIN_21")
#define ALT_0_PIN_FUNCTION  ("ALT_0")
#define ALT_1_PIN_FUNCTION  ("ALT_1")
#define ALT_2_PIN_FUNCTION  ("ALT_2")
#define ALT_3_PIN_FUNCTION  ("ALT_3")
#define ALT_4_PIN_FUNCTION  ("ALT_4")
#define ALT_5_PIN_FUNCTION  ("ALT_5")
#define INPUT_PIN_FUNCTION  ("INPUT")
#define OUTPUT_PIN_FUNCTION ("OUTPUT")

static JNIEnv *jniEnv = NULL;
static jobject inputPin = NULL;
static jobject outputPin = NULL;
static jobject alt0PinFunction = NULL;
static jobject alt1PinFunction = NULL;
static jobject alt2PinFunction = NULL;
static jobject alt3PinFunction = NULL;
static jobject alt4PinFunction = NULL;
static jobject alt5PinFunction = NULL;
static jobject inputPinFunction = NULL;
static jobject outputPinFunction = NULL;

int initGpioSuite (void) {

    if (getJNIEnv (&jniEnv) == JVM_UNSUCCESS || jniSetup (jniEnv) == JNI_ERROR) {
        return SCENARIO_FAIL;
    }

    jclass pinClass = (*jniEnv)->FindClass (jniEnv, "com/comert/gEmbedded/api/device/gpio/pin/Pin");
    jclass pinFunctionClass = (*jniEnv)->FindClass (jniEnv, "com/comert/gEmbedded/api/device/gpio/pin/PinFunction");

    if (pinClass == NULL || pinFunctionClass == NULL) {
        (*jniEnv)->ExceptionDescribe (jniEnv);
        (*jniEnv)->ExceptionClear (jniEnv);
        return SCENARIO_FAIL;
    } else {
        jfieldID inputPinId;
        jfieldID outputPinId;
        jfieldID alt0PinFunctionId;
        jfieldID alt1PinFunctionId;
        jfieldID alt2PinFunctionId;
        jfieldID alt3PinFunctionId;
        jfieldID alt4PinFunctionId;
        jfieldID alt5PinFunctionId;
        jfieldID inputPinFunctionId;
        jfieldID outputPinFunctionId;

        inputPinId = (*jniEnv)->GetStaticFieldID (jniEnv, pinClass, READER_PIN,
                                                  "Lcom/comert/gEmbedded/api/device/gpio/pin/Pin;");
        outputPinId = (*jniEnv)->GetStaticFieldID (jniEnv, pinClass, WRITER_PIN,
                                                   "Lcom/comert/gEmbedded/api/device/gpio/pin/Pin;");
        alt0PinFunctionId = (*jniEnv)->GetStaticFieldID (jniEnv, pinFunctionClass, ALT_0_PIN_FUNCTION,
                                                         "Lcom/comert/gEmbedded/api/device/gpio/pin/PinFunction;");
        alt1PinFunctionId = (*jniEnv)->GetStaticFieldID (jniEnv, pinFunctionClass, ALT_1_PIN_FUNCTION,
                                                         "Lcom/comert/gEmbedded/api/device/gpio/pin/PinFunction;");
        alt2PinFunctionId = (*jniEnv)->GetStaticFieldID (jniEnv, pinFunctionClass, ALT_2_PIN_FUNCTION,
                                                         "Lcom/comert/gEmbedded/api/device/gpio/pin/PinFunction;");
        alt3PinFunctionId = (*jniEnv)->GetStaticFieldID (jniEnv, pinFunctionClass, ALT_3_PIN_FUNCTION,
                                                         "Lcom/comert/gEmbedded/api/device/gpio/pin/PinFunction;");
        alt4PinFunctionId = (*jniEnv)->GetStaticFieldID (jniEnv, pinFunctionClass, ALT_4_PIN_FUNCTION,
                                                         "Lcom/comert/gEmbedded/api/device/gpio/pin/PinFunction;");
        alt5PinFunctionId = (*jniEnv)->GetStaticFieldID (jniEnv, pinFunctionClass, ALT_5_PIN_FUNCTION,
                                                         "Lcom/comert/gEmbedded/api/device/gpio/pin/PinFunction;");
        inputPinFunctionId = (*jniEnv)->GetStaticFieldID (jniEnv, pinFunctionClass, INPUT_PIN_FUNCTION,
                                                          "Lcom/comert/gEmbedded/api/device/gpio/pin/PinFunction;");
        outputPinFunctionId = (*jniEnv)->GetStaticFieldID (jniEnv, pinFunctionClass, OUTPUT_PIN_FUNCTION,
                                                           "Lcom/comert/gEmbedded/api/device/gpio/pin/PinFunction;");

        if ((*jniEnv)->ExceptionCheck (jniEnv) == JNI_TRUE) {
            (*jniEnv)->ExceptionDescribe (jniEnv);
            (*jniEnv)->ExceptionClear (jniEnv);
            return SCENARIO_FAIL;
        } else {
            inputPin = (*jniEnv)->GetStaticObjectField (jniEnv, pinClass, inputPinId);
            outputPin = (*jniEnv)->GetStaticObjectField (jniEnv, pinClass, outputPinId);
            alt0PinFunction = (*jniEnv)->GetStaticObjectField (jniEnv, pinFunctionClass, alt0PinFunctionId);
            alt1PinFunction = (*jniEnv)->GetStaticObjectField (jniEnv, pinFunctionClass, alt1PinFunctionId);
            alt2PinFunction = (*jniEnv)->GetStaticObjectField (jniEnv, pinFunctionClass, alt2PinFunctionId);
            alt3PinFunction = (*jniEnv)->GetStaticObjectField (jniEnv, pinFunctionClass, alt3PinFunctionId);
            alt4PinFunction = (*jniEnv)->GetStaticObjectField (jniEnv, pinFunctionClass, alt4PinFunctionId);
            alt5PinFunction = (*jniEnv)->GetStaticObjectField (jniEnv, pinFunctionClass, alt5PinFunctionId);
            inputPinFunction = (*jniEnv)->GetStaticObjectField (jniEnv, pinFunctionClass, inputPinFunctionId);
            outputPinFunction = (*jniEnv)->GetStaticObjectField (jniEnv, pinFunctionClass, outputPinFunctionId);
            if ((*jniEnv)->ExceptionCheck (jniEnv) == JNI_TRUE) {
                (*jniEnv)->ExceptionDescribe (jniEnv);
                (*jniEnv)->ExceptionClear (jniEnv);
                return SCENARIO_FAIL;
            }
        }
    }

    return SCENARIO_SUCCESS;
}

int cleanupGpioSuite (void) {

    if (jniShutdown (jniEnv) == JNI_ERROR) {
        return SCENARIO_FAIL;
    }

    jniEnv = NULL;
    inputPin = NULL;
    outputPin = NULL;
    alt0PinFunction = NULL;
    alt1PinFunction = NULL;
    alt2PinFunction = NULL;
    alt3PinFunction = NULL;
    alt4PinFunction = NULL;
    alt5PinFunction = NULL;
    inputPinFunction = NULL;
    outputPinFunction = NULL;

    return SCENARIO_SUCCESS;
}

void testGpioDriverSetup (void) {
    GPIO_STATUS status;

    status = gpioDriverSetup (NULL);
    CU_ASSERT_EQUAL(status, GPIO_ERROR)

    status = gpioDriverSetup (jniEnv);
    CU_ASSERT_EQUAL(status, GPIO_SUCCESS);

    // second setup fails
    status = gpioDriverSetup (jniEnv);
    CU_ASSERT_EQUAL(status, GPIO_ERROR);
}

void testSetPinFunction (void) {
    Java_com_comert_gEmbedded_nativeinterface_GPIOController_setPinFunction (jniEnv, NULL, inputPin, NULL);
    CU_ASSERT_EQUAL((*jniEnv)->ExceptionCheck (jniEnv), JNI_TRUE)
    (*jniEnv)->ExceptionClear (jniEnv);

    Java_com_comert_gEmbedded_nativeinterface_GPIOController_setPinFunction (jniEnv, NULL, NULL, inputPinFunction);
    CU_ASSERT_EQUAL((*jniEnv)->ExceptionCheck (jniEnv), JNI_TRUE)
    (*jniEnv)->ExceptionClear (jniEnv);


}

void testReadPinFunction (void) {}

void testSetPullUpDownStatus (void) {}

void testReadPullUpDownStatus (void) {}

void testSetEventDetectStatus (void) {}

void testReadEventDetectStatus (void) {}

void testGetRegisterSelector (void) {}

void testGetPinset (void) {}

void testIsHigh (void) {}

void testIsLow (void) {}

void testWrite (void) {}

void testClear (void) {}

void testPulse (void) {}

void testPoll (void) {}

void testReleaseGPIOThreadRecourse (void) {}

void testGpioDriverShutdown (void) {
    GPIO_STATUS status;

    status = gpioDriverShutdown (NULL);
    CU_ASSERT_EQUAL(status, GPIO_ERROR)

    status = gpioDriverShutdown (jniEnv);
    CU_ASSERT_EQUAL(status, GPIO_SUCCESS)

    // second shutdown fails
    status = gpioDriverShutdown (jniEnv);
    CU_ASSERT_EQUAL(status, GPIO_ERROR)
}

/*
int initGpioSuite (void) {
    GPIO_STATUS status = gpioDriverSetup ();
    if (status != GPIO_SUCCESS) {
        return SCENARIO_FAIL;
    }

    gpioDriver.setPinFunction (readerPin, readerFunction);
    readerRegisterSelector = gpioDriver.getRegisterSelector (readerPin);
    readerPinSet = gpioDriver.getPinset (readerPin);

    gpioDriver.setPinFunction (writerPin, writerFunction);
    writerRegisterSelector = gpioDriver.getRegisterSelector (writerPin);
    writerPinSet = gpioDriver.getPinset (writerPin);


    return SCENARIO_SUCCESS;
}

int cleanupGpioSuite (void) {
    GPIO_STATUS status = gpioDriverShutdown ();
    if (status != GPIO_SUCCESS) {
        return SCENARIO_FAIL;
    }

    return SCENARIO_SUCCESS;
}

void testWrite () {

    gpioDriver.write (writerRegisterSelector, writerPinSet);
    CU_ASSERT_EQUAL(gpioDriver.isHigh (writerRegisterSelector, writerPinSet), JNI_TRUE)
    CU_ASSERT_EQUAL(gpioDriver.isLow (writerRegisterSelector, writerPinSet), JNI_FALSE)
    CU_ASSERT_EQUAL(gpioDriver.isHigh(readerRegisterSelector, readerPinSet), JNI_TRUE)
    CU_ASSERT_EQUAL(gpioDriver.isLow(readerRegisterSelector, readerPinSet), JNI_FALSE)
    gpioDriver.clear (writerRegisterSelector, writerPinSet);
    CU_ASSERT_EQUAL(gpioDriver.isHigh (writerRegisterSelector, writerPinSet), JNI_FALSE)
    CU_ASSERT_EQUAL(gpioDriver.isLow (writerRegisterSelector, writerPinSet), JNI_TRUE)
    CU_ASSERT_EQUAL(gpioDriver.isHigh(readerRegisterSelector, readerPinSet), JNI_FALSE)
    CU_ASSERT_EQUAL(gpioDriver.isLow(readerRegisterSelector, readerPinSet), JNI_TRUE)

}

*/