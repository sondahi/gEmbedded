package com.comert.gEmbedded.nativeinterface;

import com.comert.gEmbedded.api.device.exception.JNIException;
import com.comert.gEmbedded.api.device.i2c.master.I2CBus;

public abstract class I2CMasterController {

    private I2CMasterController() {
    }

    public static native void setMaster(I2CBus bus, String enumMethodName, String enumMethodSignature, int busClockInHertz, int busClockStretchTimeout) throws JNIException;

    public static native void sendData(int busSelector, byte slaveAddress, byte[] dataToSend, int dataToSendSize) throws JNIException;

    public static native void receiveData(int busSelector, byte slaveAddress, int[] dataToReceive, int dataToReceiveSize) throws JNIException;

    public static native void sendAndReceiveData(int busSelector, byte slaveAddress, byte[] dataToSend, int dataToSendSize, int[] dataToReceive, int dataToReceiveSize) throws JNIException;

    public static native void writeRegister(int busSelector, byte slaveAddress, byte registerAddress, byte dataToSend) throws JNIException;

    public static native int readRegister(int busSelector, byte slaveAddress, byte registerAddress) throws JNIException;

    public static native int writeAndReadRegister(int busSelector, byte slaveAddress, byte registerAddress, byte dataToSend) throws JNIException;

    public static native void write(int busSelector, byte slaveAddress, byte dataToSend) throws JNIException;

    public static native int read(int busSelector, byte slaveAddress ) throws JNIException;

}
