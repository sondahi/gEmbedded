#ifndef GPIODRIVERTEST_H
#define GPIODRIVERTEST_H

int initGPIODriverSuite (void);
int cleanupGPIODriverSuite (void);

void testGPIODriverSetup(void );
void test(void );
void testGPIODriverShutdown(void );


#define GPIO_DRIVER_TEST \
    CU_TestInfo gpioDriverTests[] = { \
        { "testGPIODriverSetup", testGPIODriverSetup }, \
        { "test", test }, \
        { "testGPIODriverShutdown", testGPIODriverShutdown }, \
        CU_TEST_INFO_NULL }; \

#endif
