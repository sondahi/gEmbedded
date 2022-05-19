#ifndef GPIOTEST_H
#define GPIOTEST_H

#include "gpio.h"
#include "com_comert_gEmbedded_nativeinterface_GPIOController.h"

int initGpioSuite(void);
int cleanupGpioSuite(void);
void testWrite(void);

#define GPIO_TEST \
    CU_TestInfo gpioTests[] = { \
        { "testWrite", testWrite }, \
        CU_TEST_INFO_NULL }; \

#endif
