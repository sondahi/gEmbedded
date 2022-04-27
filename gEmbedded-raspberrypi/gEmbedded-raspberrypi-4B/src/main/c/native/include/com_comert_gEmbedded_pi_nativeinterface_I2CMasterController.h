/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_comert_gEmbedded_pi_nativeinterface_I2CMasterController */

#ifndef _Included_com_comert_gEmbedded_pi_nativeinterface_I2CMasterController
#define _Included_com_comert_gEmbedded_pi_nativeinterface_I2CMasterController
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_comert_gEmbedded_pi_nativeinterface_I2CMasterController
 * Method:    setMaster
 * Signature: (Lcom/comert/gEmbedded/api/device/i2c/master/I2CBus;Ljava/lang/String;Ljava/lang/String;II)V
 */
JNIEXPORT void JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_I2CMasterController_setMaster
  (JNIEnv *, jclass, jobject, jstring, jstring, jint, jint);

/*
 * Class:     com_comert_gEmbedded_pi_nativeinterface_I2CMasterController
 * Method:    sendData
 * Signature: (IB[BI)V
 */
JNIEXPORT void JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_I2CMasterController_sendData
  (JNIEnv *, jclass, jint, jbyte, jbyteArray, jint);

/*
 * Class:     com_comert_gEmbedded_pi_nativeinterface_I2CMasterController
 * Method:    receiveData
 * Signature: (IB[II)V
 */
JNIEXPORT void JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_I2CMasterController_receiveData
  (JNIEnv *, jclass, jint, jbyte, jintArray, jint);

/*
 * Class:     com_comert_gEmbedded_pi_nativeinterface_I2CMasterController
 * Method:    sendAndReceiveData
 * Signature: (IB[BI[II)V
 */
JNIEXPORT void JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_I2CMasterController_sendAndReceiveData
  (JNIEnv *, jclass, jint, jbyte, jbyteArray, jint, jintArray, jint);

/*
 * Class:     com_comert_gEmbedded_pi_nativeinterface_I2CMasterController
 * Method:    writeRegister
 * Signature: (IBBB)V
 */
JNIEXPORT void JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_I2CMasterController_writeRegister
  (JNIEnv *, jclass, jint, jbyte, jbyte, jbyte);

/*
 * Class:     com_comert_gEmbedded_pi_nativeinterface_I2CMasterController
 * Method:    readRegister
 * Signature: (IBB)I
 */
JNIEXPORT jint JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_I2CMasterController_readRegister
  (JNIEnv *, jclass, jint, jbyte, jbyte);

/*
 * Class:     com_comert_gEmbedded_pi_nativeinterface_I2CMasterController
 * Method:    writeAndReadRegister
 * Signature: (IBBB)I
 */
JNIEXPORT jint JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_I2CMasterController_writeAndReadRegister
  (JNIEnv *, jclass, jint, jbyte, jbyte, jbyte);

/*
 * Class:     com_comert_gEmbedded_pi_nativeinterface_I2CMasterController
 * Method:    write
 * Signature: (IBB)V
 */
JNIEXPORT void JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_I2CMasterController_write
  (JNIEnv *, jclass, jint, jbyte, jbyte);

/*
 * Class:     com_comert_gEmbedded_pi_nativeinterface_I2CMasterController
 * Method:    read
 * Signature: (IB)I
 */
JNIEXPORT jint JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_I2CMasterController_read
  (JNIEnv *, jclass, jint, jbyte);

#ifdef __cplusplus
}
#endif
#endif
