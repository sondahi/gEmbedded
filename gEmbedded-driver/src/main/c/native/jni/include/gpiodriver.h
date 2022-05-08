#ifndef GPIODRIVER_H
#define GPIODRIVER_H

#include <jni.h>

typedef enum GPIO_STATUS_ {
    GPIO_SUCCESS,
    GPIO_EXCEPTION_OCCURRED,
    GPIO_DEVICE_FILE_OPEN_ERROR,
    GPIO_MEMORY_MAP_ERROR,
    GPIO_MEMORY_UNMAP_ERROR,
    GPIO_PIN_FUNCTION_ERROR,
    GPIO_PUD_STATUS_ERROR,
    GPIO_GET_LINE_EVENT_IOCTL_ERROR,
} GPIO_STATUS;

typedef struct GPIODriver_ {

    GPIO_STATUS (*setPinFunction) (jint pinNumber, jint pinFunction);

    GPIO_STATUS (*setPUDStatus) (jint pinNumber, jint pullUpDownStatus);

    GPIO_STATUS (*setEventDetectStatus) (jint pinNumber, jint eventDetectionStatus, const char *fileName);

    void (*releaseGPIOThreadSource) (jint pinNumber);

    jint (*getRegisterSelector) (jint pinNumber);

    jint (*getPinset) (jint pinNumber);

    jboolean (*isHigh) (jint registerSelector, jint pinSet);

    jboolean (*isLow) (jint registerSelector, jint pinSet);

    void (*write) (jint registerSelector, jint pinSet);

    void (*clear) (jint registerSelector, jint pinSet);

    void (*pulse) (jint registerSelector, jint pinSet, jint highSleepTimeInMicSec, jint lowSleepTimeInMicSec);

    int (*poll) (jint pinNumber, jint timeoutInMilSec);
} GPIODriver;

extern GPIODriver gpioDriver;

GPIO_STATUS gpioDriverSetup ();

GPIO_STATUS gpioDriverShutdown ();

GPIO_STATUS gpioStatusCheck (JNIEnv *env, GPIO_STATUS status);

#endif