#ifndef GPIO_H
#define GPIO_H

#include <jni.h>

typedef enum GPIO_STATUS_ {
    GPIO_SUCCESS,
    GPIO_ERROR
} GPIO_STATUS;

GPIO_STATUS gpioDriverSetup (JNIEnv *env);

GPIO_STATUS gpioDriverShutdown (JNIEnv *env);

#endif
