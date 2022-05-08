package com.comert.gEmbedded.nativeinterface;

import com.comert.gEmbedded.api.device.exception.JNIException;
import com.comert.gEmbedded.api.device.gpio.pin.Pin;
import com.comert.gEmbedded.api.device.i2c.master.I2CBus;

public abstract class I2CMasterController {

    private I2CMasterController() {
    }

    public static native void setMaster(I2CBus bus, int busClockInHertz, int busClockStretchTimeout) throws JNIException;

    public static native int getRegisterSelector(Pin pin);

    public static native void sendData(int registerSelector, byte slaveAddress, byte[] dataToSend, int dataToSendSize) throws JNIException;

    public static native void receiveData(int registerSelector, byte slaveAddress, int[] dataToReceive, int dataToReceiveSize) throws JNIException;

    public static native void sendAndReceiveData(int registerSelector, byte slaveAddress, byte[] dataToSend, int dataToSendSize, int[] dataToReceive, int dataToReceiveSize) throws JNIException;

    public static native void writeRegister(int registerSelector, byte slaveAddress, byte registerAddress, byte dataToSend) throws JNIException;

    public static native int readRegister(int registerSelector, byte slaveAddress, byte registerAddress) throws JNIException;

    public static native int writeAndReadRegister(int registerSelector, byte slaveAddress, byte registerAddress, byte dataToSend) throws JNIException;

    public static native void write(int registerSelector, byte slaveAddress, byte dataToSend) throws JNIException;

    public static native int read(int registerSelector, byte slaveAddress) throws JNIException;

}