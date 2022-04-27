/**
 * @author Gökay Cömert
 */

#include "com_comert_gEmbedded_pi_nativeinterface_I2CMasterController.h"
#include "i2cmasterdriver.h"

#include "jnicontroller.h"

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_I2CMasterController_setMaster
(JNIEnv *env, const jclass I2CMasterController, jobject bus, const jstring methodName, const jstring methodSignature,
 const jint busClockInHertz, const jint busClockStretchTimeout) {

    jint busNumber;

    const register JNI_STATUS busStatus = jniController.getConstantDigit(env, bus, methodName, methodSignature, &busNumber);
    if(busStatus == JNI_EXCEPTION_OCCURRED){
        return;
    }

    const register I2C_STATUS i2CStatus = i2CMasterDriver.configure(busNumber, busClockInHertz, busClockStretchTimeout);

    const register I2C_STATUS i2cExceptionStatus = i2cStatusCheck(env,i2CStatus);
    if( i2cExceptionStatus == I2C_EXCEPTION_OCCURRED){
        return;
    }

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_I2CMasterController_sendData
(JNIEnv *env, const jclass I2CMasterController, const jint busSelector, const jbyte slaveAddress,
 const jbyteArray dataToSend, const jint dataToSendSize) {

    struct MessageToSend sMessage;
    sMessage.busSelector = busSelector;
    sMessage.address = slaveAddress;
    sMessage.dataToSendSize = dataToSendSize;
    (*env)->GetByteArrayRegion(env, dataToSend, 0, dataToSendSize, (jbyte *) sMessage.dataToSend);

    const register I2C_STATUS i2CStatus = i2CMasterDriver.sendData(&sMessage);

    const register I2C_STATUS i2cExceptionStatus = i2cStatusCheck(env,i2CStatus);
    if( i2cExceptionStatus == I2C_EXCEPTION_OCCURRED){
        return;
    }

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_I2CMasterController_receiveData
(JNIEnv *env, const jclass I2CMasterController, const jint busSelector, const jbyte slaveAddress,
 const jintArray dataToReceive, const jint dataToReceiveSize) {

    struct MessageToReceive rMessage;
    rMessage.busSelector = busSelector;
    rMessage.address = slaveAddress;
    rMessage.dataToReceiveSize = dataToReceiveSize;

    const register I2C_STATUS i2CStatus = i2CMasterDriver.receiveData(&rMessage);

    const register I2C_STATUS i2cExceptionStatus = i2cStatusCheck(env,i2CStatus);
    if( i2cExceptionStatus == I2C_EXCEPTION_OCCURRED){
        return;
    }

    (*env)->SetIntArrayRegion(env, dataToReceive, 0, dataToReceiveSize, (jint *) rMessage.dataToReceive);

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_I2CMasterController_sendAndReceiveData
(JNIEnv *env, const jclass I2CMasterController, const jint busSelector, const jbyte slaveAddress,
 const jbyteArray dataToSend, const jint dataToSendSize, const jbyteArray dataToReceive, const jint dataToReceiveSize) {

    struct MessageToSendAndReceive srMessage;
    srMessage.busSelector = busSelector;
    srMessage.address = slaveAddress;
    srMessage.dataToSendSize = dataToSendSize;
    srMessage.dataToReceiveSize = dataToReceiveSize;
    (*env)->GetByteArrayRegion(env, dataToSend, 0, dataToSendSize, (jbyte *) srMessage.dataToSend);

    const register I2C_STATUS i2CStatus = i2CMasterDriver.sendAndReceiveData(&srMessage);

    const register I2C_STATUS i2cExceptionStatus = i2cStatusCheck(env,i2CStatus);
    if( i2cExceptionStatus == I2C_EXCEPTION_OCCURRED){
        return;
    }

    (*env)->SetIntArrayRegion(env, dataToReceive, 0, dataToReceiveSize, (jint *) srMessage.dataToReceive);

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_I2CMasterController_writeRegister
(JNIEnv *env, const jclass I2CMasterController, const jint busSelector, const jbyte slaveAddress,
 const jbyte registerAddress, const jbyte dataToSend) {

    struct MessageToSend sMessage;
    sMessage.busSelector = busSelector;
    sMessage.address = slaveAddress;
    sMessage.dataToSend[0] = registerAddress;
    sMessage.dataToSend[1] = dataToSend;
    sMessage.dataToSendSize = 2;

    const register I2C_STATUS i2CStatus = i2CMasterDriver.sendData(&sMessage);

    const register I2C_STATUS i2cExceptionStatus = i2cStatusCheck(env,i2CStatus);
    if( i2cExceptionStatus == I2C_EXCEPTION_OCCURRED){
        return;
    }

}

JNIEXPORT jint JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_I2CMasterController_readRegister
(JNIEnv *env, const jclass I2CMasterController, const jint busSelector, const jbyte slaveAddress, const jbyte registerAddress) {

    struct MessageToSendAndReceive srMessage;
    srMessage.busSelector = busSelector;
    srMessage.address = slaveAddress;
    srMessage.dataToSend[0] = registerAddress;
    srMessage.dataToSendSize = 1;
    srMessage.dataToReceiveSize = 1;

    const register I2C_STATUS i2CStatus = i2CMasterDriver.sendAndReceiveData(&srMessage);

    const register I2C_STATUS i2cExceptionStatus = i2cStatusCheck(env,i2CStatus);
    if( i2cExceptionStatus == I2C_EXCEPTION_OCCURRED){
        return -1;
    }

    return (jint) srMessage.dataToReceive[0];

}

JNIEXPORT jint JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_I2CMasterController_writeAndReadRegister
(JNIEnv *env, const jclass I2CMasterController, const jint busSelector, const jbyte slaveAddress,
 const jbyte registerAddress, const jbyte dataToSend) {

    struct MessageToSendAndReceive srMessage;
    srMessage.busSelector = busSelector;
    srMessage.address = slaveAddress;
    srMessage.dataToSend[0] = registerAddress;
    srMessage.dataToSend[1] = dataToSend;
    srMessage.dataToSendSize = 2;
    srMessage.dataToReceiveSize = 1;

    const register I2C_STATUS i2CStatus = i2CMasterDriver.sendAndReceiveData(&srMessage);

    const register I2C_STATUS i2cExceptionStatus = i2cStatusCheck(env,i2CStatus);
    if( i2cExceptionStatus == I2C_EXCEPTION_OCCURRED){
        return -1;
    }

    return (jint) srMessage.dataToReceive[0];

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_I2CMasterController_write
(JNIEnv *env, const jclass I2CMasterController, const jint busSelector, const jbyte slaveAddress, const jbyte dataToSend) {

    struct MessageToSend sMessage;
    sMessage.busSelector = busSelector;
    sMessage.address = slaveAddress;
    sMessage.dataToSend[0] = dataToSend;
    sMessage.dataToSendSize = 1;

    const register I2C_STATUS i2CStatus = i2CMasterDriver.sendData(&sMessage);

    const register I2C_STATUS i2cExceptionStatus = i2cStatusCheck(env,i2CStatus);
    if( i2cExceptionStatus == I2C_EXCEPTION_OCCURRED){
        return;
    }

}

JNIEXPORT jint JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_I2CMasterController_read
(JNIEnv *env, const jclass I2CMasterController, const jint busSelector, const jbyte slaveAddress) {

    struct MessageToReceive rMessage;
    rMessage.busSelector = busSelector;
    rMessage.address = slaveAddress;
    rMessage.dataToReceiveSize = 1;

    const register I2C_STATUS i2CStatus = i2CMasterDriver.receiveData(&rMessage);

    const register I2C_STATUS i2cExceptionStatus = i2cStatusCheck(env,i2CStatus);
    if( i2cExceptionStatus == I2C_EXCEPTION_OCCURRED){
        return -1;
    }

    return (jint) rMessage.dataToReceive[0];

}