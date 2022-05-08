#include <CUnit/Basic.h>
#include <unistd.h>
#include "gpiotest.h"

int initGpioSuite (void) {
    GPIO_STATUS status = gpioDriverSetup();
    return status;
}

int cleanGpioSuite (void) {
    GPIO_STATUS status = gpioDriverShutdown ();
    return status;
}

void testWrite(){

}

