package com.comert.gEmbedded.nativeinterface;

import com.comert.gEmbedded.api.device.exception.JNIException;
import com.comert.gEmbedded.api.device.gpio.pin.Pin;
import com.comert.gEmbedded.api.device.i2c.master.I2CBus;
import com.comert.gEmbedded.nativeinterface.util.NativeUtils;

import java.io.IOException;
import java.util.Set;

public abstract class DeviceController {

    static {
        //System.loadLibrary("gEmbeddedRaspi4B32");
        try {
            NativeUtils.loadLibraryFromJar("/libgEmbeddedRaspi4B32.so");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private DeviceController() {
    }

    public static native void setupDevice() throws JNIException;

    public static native void shutdownDevice() throws JNIException;

    public static native Set<Pin> getNotSupportedPins();

    public static native Set<I2CBus> getNotSupportedI2CBusses();

}
