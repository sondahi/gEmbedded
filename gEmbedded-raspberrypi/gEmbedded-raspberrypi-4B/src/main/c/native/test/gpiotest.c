#include <CUnit/Basic.h>
#include <unistd.h>
#include "gpiotest.h"

int init_gpio_suite (void) {
    GPIO_STATUS status = gpioDriverSetup();
    if(status != GPIO_SUCCESS){
        printf ("Error Code : %d\n",status);
    }
    return status;
}

int clean_gpio_suite (void) {
    GPIO_STATUS status = gpioDriverShutdown ();
    if(status != GPIO_SUCCESS){
        printf ("Error Code : %d\n",status);
    }
    return status;
}

void testWrite (void) {
    jint pinNumber = 21;
    jint pinFunction = 7;
    gpioDriver.setPinFunction (pinNumber, pinFunction);
    jint registerSelector = gpioDriver.getRegisterSelector (pinNumber);
    jint pinSet = gpioDriver.getPinset (pinNumber);
    gpioDriver.write (registerSelector, pinSet);
    sleep (5);
    gpioDriver.clear (registerSelector, pinSet);
}

