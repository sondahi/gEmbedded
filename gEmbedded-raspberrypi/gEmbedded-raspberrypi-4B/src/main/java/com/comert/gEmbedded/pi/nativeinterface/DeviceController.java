package com.comert.gEmbedded.pi.nativeinterface;

import com.comert.gEmbedded.api.device.common.exception.JNIException;
import com.comert.gEmbedded.pi.nativeinterface.util.NativeUtils;

import java.io.IOException;

public abstract class DeviceController {

    static {
        //System.loadLibrary("gEmbeddedRasPi4B32");
        try {
            NativeUtils.loadLibraryFromJar("/libgEmbeddedRasPi4B32.so");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private DeviceController() {
    }

    public static native void setUpJNIDriver(String jniExceptionClass) throws JNIException;

    public static native void shutDownJNIDriver() throws JNIException;

    public static native void setUpGpioDriver(String memoryFileName, int gpioBaseAddress, int gpioBlockSize) throws JNIException;

    public static native void shutDownGpioDriver(int gpioBlockSize) throws JNIException;

    public static native void setUpI2CMasterDriver(String memoryFileName, int bscBaseAddress, int bscBlockSize, int busNumber) throws JNIException;

    public static native void shutDownI2CMasterDriver(int bscBlockSize, int busNumber) throws JNIException;

}
