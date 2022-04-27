/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   gpioexception.h
 * Author: Gökay Cömert
 *
 * Created on 17. April 2022, 22:29
 */

#ifndef GPIOEXCEPTION_H
#define GPIOEXCEPTION_H

#ifdef __cplusplus
extern "C" {
#endif

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

    extern GPIO_STATUS gpioStatusCheck(JNIEnv *, GPIO_STATUS);

#ifdef __cplusplus
}
#endif

#endif /* GPIOEXCEPTION_H */
