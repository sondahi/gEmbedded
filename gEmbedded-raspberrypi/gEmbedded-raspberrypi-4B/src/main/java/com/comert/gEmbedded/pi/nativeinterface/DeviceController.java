package com.comert.gEmbedded.pi.nativeinterface;

import com.comert.gEmbedded.api.device.common.exception.JNIException;
import com.comert.gEmbedded.pi.nativeinterface.util.NativeUtils;

import java.io.IOException;

public abstract class DeviceController {

    static {
        System.loadLibrary("gEmbeddedRaspi4B");
        /*
        try {
            NativeUtils.loadLibraryFromJar("/libgEmbeddedRasPi4B32.so");
        } catch (IOException e) {
            e.printStackTrace();
        }
         */
    }

    private DeviceController() {
    }

    public static native void setUpJNIDriver(String jniExceptionClass) throws JNIException;

    public static native void shutDownJNIDriver() throws JNIException;

    public static native void setUpGpioDriver() throws JNIException;

    public static native void shutDownGpioDriver() throws JNIException;

    public static native void setUpI2CMasterDriver(int busNumber) throws JNIException;

    public static native void shutDownI2CMasterDriver(int busNumber) throws JNIException;

}
