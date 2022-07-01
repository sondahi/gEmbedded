/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   i2cmasterexception.h
 * Author: Gökay Cömert
 *
 * Created on 17. April 2022, 22:29
 */

#ifndef I2CMASTEREXCEPTION_H
#define I2CMASTEREXCEPTION_H

#ifdef __cplusplus
extern "C" {
#endif

#include <jni.h>

    typedef enum I2C_STATUS_ {
        I2C_SUCCESS,
        I2C_EXCEPTION_OCCURRED,
        I2C_UNSUPPORTED_BUS_ERROR,
        I2C_BUS_DEV_FILE_OPEN_ERROR,
        I2C_BUS_MEM_MAP_ERROR,
        I2C_BUS_MEM_UNMAP_ERROR,
        I2C_BUS_DIV_ERROR,
        I2C_BUS_CLKT_ERROR,
        I2C_SLAVE_SEND_ACK_ERROR,
        I2C_SLAVE_SEND_CLOCK_TIMEOUT_ERROR,
        I2C_SLAVE_SEND_DATA_LOSS_ERROR,
        I2C_SLAVE_RECEIVE_ACK_ERROR,
        I2C_SLAVE_RECEIVE_CLOCK_TIMEOUT_ERROR,
        I2C_SLAVE_RECEIVE_DATA_LOSS_ERROR
    } I2C_STATUS;

    extern I2C_STATUS i2cStatusCheck(JNIEnv *, I2C_STATUS);

#ifdef __cplusplus
}
#endif

#endif /* I2CMASTEREXCEPTION_H */