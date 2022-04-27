/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   gpiodriver.h
 * Author: Gökay Cömert
 *
 * Created on 17. April 2022, 22:29
 */

#ifndef GPIODRIVER_H
#define GPIODRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "gpioexception.h"
#include <jni.h>

    typedef struct GPIODriver_ {
        GPIO_STATUS(*setPinFunction)(jint pinNumber, jint pinFunction);
        GPIO_STATUS(*setPUDStatus)(jint pinNumber, jint pullUpDownStatus);
        GPIO_STATUS(*setEventDetectStatus)(jint pinNumber, jint eventDetectionStatus, const char *fileName);
        jint(*readPinFunction)(jint pinNumber);
        void (*releaseGPIOThreadSource)(jint pinNumber);
        jboolean(*isHigh)(jint registerSelector, jint pinSet);
        jboolean(*isLow)(jint registerSelector, jint pinSet);
        void (*write)(jint registerSelector, jint pinSet);
        void (*clear)(jint registerSelector, jint pinSet);
        void (*pulse)(jint registerSelector, jint pinSet, jint highSleepTimeInMicSec, jint lowSleepTimeInMicSec);
        jint(*poll)(jint pinNumber, jint timeoutInMilSec);
    } GPIODriver;

    extern GPIODriver gpioDriver;

    GPIO_STATUS gpioDriverSetup(void);
    GPIO_STATUS gpioDriverShutdown(void);

#ifdef __cplusplus
}
#endif

#endif /* GPIODRIVER_H */
