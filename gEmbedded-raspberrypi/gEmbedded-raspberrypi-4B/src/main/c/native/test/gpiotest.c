#include <CUnit/Basic.h>
#include <unistd.h>
#include "gpiotest.h"

int init_gpio_suite(void) {
    GPIO_STATUS status = gpioDriverSetup();
    return status;
}

int clean_gpio_suite(void) {
    GPIO_STATUS status = gpioDriverShutdown();
    return status;
}

void testWrite(void){
    int pinNumber = 21;
    int pinFunction = 1;
        gpioDriver.setPinFunction(pinNumber,pinFunction);
        int registerSelector = gpioDriver.getRegisterSelector(pinNumber);
        int pinSet = gpioDriver.getPinset(pinNumber);
        gpioDriver.write(registerSelector, pinSet);
    sleep(2);
    gpioDriver.clear(registerSelector, pinSet);
}

