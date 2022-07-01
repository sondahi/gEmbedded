#ifndef GPIOTEST_H
#define GPIOTEST_H

int initGpioSuite (void);

int cleanupGpioSuite (void);

void testGpioDriverSetup (void);

void testSetPinFunction (void);

void testReadPinFunction (void);

void testSetPullUpDownStatus (void);

void testReadPullUpDownStatus (void);

void testSetEventDetectStatus (void);

void testReadEventDetectStatus (void);

void testGetRegisterSelector (void);

void testGetPinset (void);

void testIsHigh (void);

void testIsLow (void);

void testWrite (void);

void testClear (void);

void testPulse (void);

void testPoll (void);

void testReleaseGPIOThreadRecourse (void);

void testGpioDriverShutdown (void);

#define GPIO_TEST \
    CU_TestInfo gpioTests[] = { \
        { "testGpioDriverSetup", testGpioDriverSetup }, \
        { "testSetPinFunction", testSetPinFunction },   \
        { "testReadPinFunction", testReadPinFunction }, \
        { "testSetPullUpDownStatus", testSetPullUpDownStatus }, \
        { "testReadPullUpDownStatus", testReadPullUpDownStatus }, \
        { "testSetEventDetectStatus", testSetEventDetectStatus }, \
        { "testReadEventDetectStatus", testReadEventDetectStatus }, \
        { "testGetRegisterSelector", testGetRegisterSelector }, \
        { "testGetPinset", testGetPinset }, \
        { "testIsHigh", testIsHigh }, \
        { "testIsLow", testIsLow }, \
        { "testWrite", testWrite }, \
        { "testClear", testClear }, \
        { "testPulse", testPulse }, \
        { "testPoll", testPoll }, \
        { "testReleaseGPIOThreadRecourse", testReleaseGPIOThreadRecourse }, \
        { "testGpioDriverShutdown", testGpioDriverShutdown }, \
        CU_TEST_INFO_NULL }; \

#endif
