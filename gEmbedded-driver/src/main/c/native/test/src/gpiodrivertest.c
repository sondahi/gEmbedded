#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <CUnit/Basic.h>
#include "commontest.h"
#include "gpiodriver.h"
#include "gpiodrivertest.h"

static void *gpioOffset;

int initGPIODriverSuite (void) {

    int memoryFileDescriptor = open (GPIO_MEM_DEV_NAME, O_RDWR | O_SYNC);

    if (memoryFileDescriptor < 0) {
        close (memoryFileDescriptor);
        return SCENARIO_FAIL;
    }

    gpioOffset = mmap (NULL, GPIO_BLOCK_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, memoryFileDescriptor,
                       0);
    if (gpioOffset == MAP_FAILED) {
        close (memoryFileDescriptor);
        return SCENARIO_FAIL;
    }

    close (memoryFileDescriptor);

    return SCENARIO_SUCCESS;
}

int cleanupGPIODriverSuite (void) {

    const int memoryUnmap = munmap (gpioOffset, GPIO_BLOCK_SIZE);

    if (memoryUnmap < 0) {
        return SCENARIO_FAIL;
    }

    gpioOffset = NULL;

    return SCENARIO_SUCCESS;
}

void testGPIODriverSetup (void) {
    GPIO_STATUS status = gpioDriverSetup (gpioOffset);
    CU_ASSERT_EQUAL(status, GPIO_SUCCESS)
}

void testPinWrite (void) {
    register const GPIO_PIN pin = PIN_21;
    setPinFunction (pin, FUNCTION_OUTPUT);

    register const u8 registerSelector = calculate1bitRegisterSelector (pin);
    register const u32 pinSet = calculate1bitPinSet (pin);

    for (register int i = 0; i < 10; ++i) {
        register u32 highSleepTime;
        register u32 lowSleepTime;

        for (register int j = 0; j < 45; ++j) {
            highSleepTime = (u32) (500 + (44.4 * j));
            lowSleepTime = 20000 - highSleepTime;
            pulsePinFaster (registerSelector, pinSet, highSleepTime, lowSleepTime);
        }

        for (register int j = 45; j > 0; --j) {
            highSleepTime = (u32) (500 + (44.4 * j));
            lowSleepTime = 20000 - highSleepTime;
            pulsePinFaster (registerSelector, pinSet, highSleepTime, lowSleepTime);
        }

    }
}

void testEvent (void) {

    register const GPIO_PIN trigger = PIN_20;
    setPinFunction (trigger, FUNCTION_OUTPUT);
    CU_ASSERT_EQUAL(readPinFunction (trigger), FUNCTION_OUTPUT)
    register const u8 registerSelector = calculate1bitRegisterSelector (trigger);
    register const u32 pinSet = calculate1bitPinSet (trigger);

    register const GPIO_PIN listener = PIN_21;
    GPIO_STATUS status = setEventDetectStatus (listener, EVENT_BOTH_EDGES);
    CU_ASSERT_EQUAL(status, GPIO_SUCCESS)

    register GPIO_EVENT_RESULT result;

    writePinFaster (registerSelector, pinSet);
    result = pollEvent (listener, 10);
    CU_ASSERT_EQUAL(result, EVENT_RISING)
    printf ("Event Result : %d\n", result);

    clearPin (registerSelector, pinSet);
    result = pollEvent (listener, 10);
    CU_ASSERT_EQUAL(result, EVENT_FALLING)
    printf ("Event Result : %d\n", result);

}

void testCalculates (void) {
    u8 regSelResult;
    u32 pinSetResult;

    regSelResult = calculate1bitRegisterSelector (16);
    CU_ASSERT_EQUAL(regSelResult, 0)
    pinSetResult = calculate1bitPinSet (16);
    CU_ASSERT_EQUAL(pinSetResult, 0x00010000)

    regSelResult = calculate1bitRegisterSelector (31);
    CU_ASSERT_EQUAL(regSelResult, 0)
    pinSetResult = calculate1bitPinSet (31);
    CU_ASSERT_EQUAL(pinSetResult, 0x80000000)

}

void test (void) {

    register const GPIO_PIN input = PIN_21;
    register const u8 registerSelector = calculate1bitRegisterSelector (input);
    register const u32 pinSet = calculate1bitPinSet (input);
    setPinFunction (input,FUNCTION_INPUT);
    setPullupPulldown(input,PUPPDN_PULL_UP);

    while (1){

        GPIO_PIN_LEVEL pinLevel = readPinLevel (registerSelector,pinSet);
        if (pinLevel == LEVEL_HIGH){
            break;
        }
    }

}

void testGPIODriverShutdown (void) {
    GPIO_STATUS status = gpioDriverShutdown ();
    CU_ASSERT_EQUAL(status, GPIO_SUCCESS)
}
