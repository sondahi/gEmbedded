package com.comert.gEmbedded.pi.nativeinterface;

import com.comert.gEmbedded.api.device.common.exception.JNIException;
import com.comert.gEmbedded.pi.nativeinterface.util.NativeUtils;

import java.io.IOException;

public abstract class DeviceController {

    static {
        /*
        if (System.getProperty("os.arch").equals("aarch64")){
            System.loadLibrary("gEmbeddedRaspi4B64");
        } else {
            System.loadLibrary("gEmbeddedRaspi4B32");
        }
         */

        try {
            if (System.getProperty("os.arch").equals("aarch64")){
                NativeUtils.loadLibraryFromJar("/libgEmbeddedRaspi4B64.so");
            } else {
                NativeUtils.loadLibraryFromJar("/libgEmbeddedRaspi4B32.so");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

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
