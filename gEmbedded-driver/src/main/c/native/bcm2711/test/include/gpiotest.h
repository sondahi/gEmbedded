#ifndef GPIOTEST_H
#define GPIOTEST_H

#include "gpiodriver.h"

int initGpioSuite(void);
int cleanupGpioSuite(void);
void testWrite(void);

#define GPIO_TEST \
    CU_TestInfo gpioTests[] = { \
        { "testWrite", testWrite }, \
        CU_TEST_INFO_NULL }; \

#endif
