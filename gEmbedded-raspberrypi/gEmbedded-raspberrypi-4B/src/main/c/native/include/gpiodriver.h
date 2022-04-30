#ifndef GPIODRIVER_H
#define GPIODRIVER_H

#include "gpioexception.h"

typedef struct GPIODriver_ {

    GPIO_STATUS (*setPinFunction) (jint pinNumber, jint pinFunction);

    GPIO_STATUS (*setPUDStatus) (jint pinNumber, jint pullUpDownStatus);

    GPIO_STATUS (*setEventDetectStatus) (jint pinNumber, jint eventDetectionStatus, const char *fileName);

    jint (*getRegisterSelector)(jint pinNumber);

    jint (*getPinset)(jint pinNumber);

    void (*releaseGPIOThreadSource) (jint pinNumber);

    jboolean (*isHigh) (jint registerSelector, jint pinSet);

    jboolean (*isLow) (jint registerSelector, jint pinSet);

    void (*write) (jint registerSelector, jint pinSet);

    void (*clear) (jint registerSelector, jint pinSet);

    void (*pulse) (jint registerSelector, jint pinSet, jint highSleepTimeInMicSec, jint lowSleepTimeInMicSec);

    int (*poll) (jint pinNumber, jint timeoutInMilSec);
} GPIODriver;

extern GPIODriver gpioDriver;

GPIO_STATUS gpioDriverSetup (off_t physicalAddress, size_t blockSize, const char *fileName);

GPIO_STATUS gpioDriverShutdown (size_t blockSize);

#endif
