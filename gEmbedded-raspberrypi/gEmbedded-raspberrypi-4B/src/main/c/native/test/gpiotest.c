#include <CUnit/Basic.h>
#include <unistd.h>
#include "gpiotest.h"

static const char *fileName = "/dev/mem";
static const size_t blockSize = 0xF4; // GPIO
static const off_t physicalAddress = 0xFE200000; // GPIO

int init_gpio_suite(void) {
    GPIO_STATUS status = gpioDriverSetup(physicalAddress,blockSize,fileName);
    return status;
}

int clean_gpio_suite(void) {
    GPIO_STATUS status = gpioDriverShutdown(blockSize);
    return status;
}

void testWrite(void){
    int pinNumber = 21;
    int pinFunction = 7;
        gpioDriver.setPinFunction(pinNumber,pinFunction);
        int registerSelector = gpioDriver.getRegisterSelector(pinNumber);
        int pinSet = gpioDriver.getPinset(pinNumber);
        gpioDriver.write(registerSelector, pinSet);
    sleep(2);
    gpioDriver.clear(registerSelector, pinSet);
}

