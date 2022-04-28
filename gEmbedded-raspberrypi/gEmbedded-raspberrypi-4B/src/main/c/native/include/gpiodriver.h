#ifndef GPIODRIVER_H
#define GPIODRIVER_H

#include "gpioexception.h"

    typedef struct GPIODriver_ {
        int (*getRegisterSelector)(int pinNumber);
        int (*getPinset)(int pinNumber);
        GPIO_STATUS(*setPinFunction)(int pinNumber, int pinFunction);
        GPIO_STATUS(*setPUDStatus)(int pinNumber, int pullUpDownStatus);
        GPIO_STATUS(*setEventDetectStatus)(int pinNumber, int eventDetectionStatus, const char *fileName);
        jint(*readPinFunction)(int pinNumber);
        void (*releaseGPIOThreadSource)(int pinNumber);
        jboolean(*isHigh)(int registerSelector, int pinSet);
        jboolean(*isLow)(int registerSelector, int pinSet);
        void (*write)(int registerSelector, int pinSet);
        void (*clear)(int registerSelector, int pinSet);
        void (*pulse)(int registerSelector, int pinSet, int highSleepTimeInMicSec, int lowSleepTimeInMicSec);
        jint(*poll)(int pinNumber, int timeoutInMilSec);
    } GPIODriver;

    extern GPIODriver gpioDriver;

    GPIO_STATUS gpioDriverSetup(void);
    GPIO_STATUS gpioDriverShutdown(void);

#endif
