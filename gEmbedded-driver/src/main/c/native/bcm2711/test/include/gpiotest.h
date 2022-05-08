#ifndef GPIOTEST_H
#define GPIOTEST_H

#include "gpiodriver.h"

int initGpioSuite(void);
int cleanGpioSuite(void);
void testPinFunction();
void testWrite(void);

#define GPIO_TEST  \
    pSuite = CU_add_suite("GPIOTest", initGpioSuite, cleanGpioSuite); \
    if (NULL == pSuite) { \
        CU_cleanup_registry(); \
        return CU_get_error(); \
    } \
    if (             \
        (NULL == CU_add_test(pSuite, "testWrite", testWrite)) \
        ) { \
        CU_cleanup_registry(); \
        return CU_get_error(); \
    }; \

#endif
