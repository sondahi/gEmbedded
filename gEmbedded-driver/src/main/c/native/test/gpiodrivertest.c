#include <CUnit/Basic.h>
#include "gpiodrivertest.h"
#include "commontest.h"

static jint readerPin = 20;
static jint readerFunction = 6;
static jint readerRegisterSelector;
static jint readerPinSet;

static jint writerPin = 21;
static jint writerFunction = 7;
static jint writerRegisterSelector;
static jint writerPinSet;

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

