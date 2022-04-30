#ifndef GPIOTEST_H
#define GPIOTEST_H

#include "gpiodriver.h"

int init_gpio_suite(void);
int clean_gpio_suite(void);
void testWrite(void);

#define GPIO_TEST  \
    pSuite = CU_add_suite("gpiotest", init_gpio_suite, clean_gpio_suite); \
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
