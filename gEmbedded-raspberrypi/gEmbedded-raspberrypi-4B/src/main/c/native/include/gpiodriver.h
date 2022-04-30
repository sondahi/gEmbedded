#ifndef GPIODRIVER_H
#define GPIODRIVER_H

#include "gpioexception.h"

typedef enum GPIO_PIN_ {
    PIN_0 = 0,
    PIN_1 = 1,
    PIN_2 = 2,
    PIN_3 = 3,
    PIN_4 = 4,
    PIN_5 = 5,
    PIN_6 = 6,
    PIN_7 = 7,
    PIN_8 = 8,
    PIN_9 = 9,
    PIN_10 = 10,
    PIN_11 = 11,
    PIN_12 = 12,
    PIN_13 = 13,
    PIN_14 = 14,
    PIN_15 = 15,
    PIN_16 = 16,
    PIN_17 = 17,
    PIN_18 = 18,
    PIN_19 = 19,
    PIN_20 = 20,
    PIN_21 = 21,
    PIN_22 = 22,
    PIN_23 = 23,
    PIN_24 = 24,
    PIN_25 = 25,
    PIN_26 = 26,
    PIN_27 = 27,
    PIN_28 = 28,
    PIN_29 = 29,
    PIN_30 = 30
} GPIO_PIN;

typedef enum GPIO_PIN_FUNCTION_ {
    INPUT = 0b000,
    OUTPUT = 0b001,
    ALT0 = 0b100,
    ALT1 = 0b101,
    ALT2 = 0b110,
    ALT3 = 0b111,
    ALT4 = 0b011,
    ALT5 = 0b010
} GPIO_PIN_FUNCTION;

typedef enum GPIO_PIN_FUNCTION_ {
    INPUT = 0b000,
    OUTPUT = 0b001,
    ALT0 = 0b100,
    ALT1 = 0b101,
    ALT2 = 0b110,
    ALT3 = 0b111,
    ALT4 = 0b011,
    ALT5 = 0b010
} GPIO_PIN_FUNCTION;

typedef struct GPIODriver_ {
    int (*getRegisterSelector) (int pinNumber);

    int (*getPinset) (int pinNumber);

    GPIO_STATUS (*setPinFunction) (GPIO_PIN gpioPin, GPIO_PIN_FUNCTION pinFunction);

    int (*getPinFunction) (GPIO_PIN gpioPin);

    GPIO_STATUS (*setPUDStatus) (GPIO_PIN gpioPin, int pullUpDownStatus);

    int (*getPUDStatus) (GPIO_PIN gpioPin, int pullUpDownStatus);

    GPIO_STATUS (*setEventDetectStatus) (GPIO_PIN gpioPin, int eventDetectionStatus, const char *fileName);

    int (*getEventDetectStatus) (GPIO_PIN gpioPin, int eventDetectionStatus, const char *fileName);

    void (*releaseGPIOThreadSource) (GPIO_PIN gpioPin);

    char (*isHigh) (int registerSelector, int pinSet);

    char (*isLow) (int registerSelector, int pinSet);

    void (*write) (int registerSelector, int pinSet);

    void (*clear) (int registerSelector, int pinSet);

    void (*pulse) (int registerSelector, int pinSet, int highSleepTimeInMicSec, int lowSleepTimeInMicSec);

    int (*poll) (GPIO_PIN gpioPin, int timeoutInMilSec);
} GPIODriver;

extern GPIODriver gpioDriver;

GPIO_STATUS gpioDriverSetup (void);

GPIO_STATUS gpioDriverShutdown (void);

#endif
