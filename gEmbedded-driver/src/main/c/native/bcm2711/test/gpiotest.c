#include <CUnit/Basic.h>
#include <unistd.h>
#include "gpiotest.h"

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
        return 1;
    }

    gpioDriver.setPinFunction (readerPin, readerFunction);
    readerRegisterSelector = gpioDriver.getRegisterSelector (readerPin);
    readerPinSet = gpioDriver.getPinset (readerPin);

    gpioDriver.setPinFunction (writerPin, writerFunction);
    writerRegisterSelector = gpioDriver.getRegisterSelector (writerPin);
    writerPinSet = gpioDriver.getPinset (writerPin);

    return 0;
}

int cleanGpioSuite (void) {
    GPIO_STATUS status = gpioDriverShutdown ();
    if (status != GPIO_SUCCESS) {
        return 1;
    }

    return 0;
}

void testWrite () {
    gpioDriver.write (writerRegisterSelector, writerPinSet);
    CU_ASSERT_EQUAL(gpioDriver.isHigh (writerRegisterSelector, writerPinSet), JNI_TRUE)
    CU_ASSERT_EQUAL(gpioDriver.isLow (writerRegisterSelector, writerPinSet), JNI_FALSE)
    CU_ASSERT_EQUAL(gpioDriver.isHigh(readerRegisterSelector, readerPinSet), JNI_TRUE)
    CU_ASSERT_EQUAL(gpioDriver.isLow(readerRegisterSelector, readerPinSet), JNI_FALSE)
    sleep (2);
    gpioDriver.clear (writerRegisterSelector, writerPinSet);
    CU_ASSERT_EQUAL(gpioDriver.isHigh (writerRegisterSelector, writerPinSet), JNI_FALSE)
    CU_ASSERT_EQUAL(gpioDriver.isLow (writerRegisterSelector, writerPinSet), JNI_TRUE)
    CU_ASSERT_EQUAL(gpioDriver.isHigh(readerRegisterSelector, readerPinSet), JNI_FALSE)
    CU_ASSERT_EQUAL(gpioDriver.isLow(readerRegisterSelector, readerPinSet), JNI_TRUE)
}

