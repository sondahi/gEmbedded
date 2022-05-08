package com.comert.gEmbedded.nativeinterface;

import com.comert.gEmbedded.api.device.exception.JNIException;
import com.comert.gEmbedded.api.device.gpio.pin.Pin;
import com.comert.gEmbedded.api.device.i2c.master.I2CBus;
import com.comert.gEmbedded.nativeinterface.util.NativeUtils;

import java.io.IOException;
import java.util.Set;

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
            final var arch = System.getProperty("os.arch");
            switch (arch){
                case "aarch64":{
                    NativeUtils.loadLibraryFromJar("/libgEmbeddedRaspi4B64.so");
                    break;
                }
                case "arm":{
                    NativeUtils.loadLibraryFromJar("/libgEmbeddedRaspi4B32.so");
                }
                default:{
                    throw new RuntimeException("Unsupported Arc");
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private DeviceController() {
    }

    public static native void setupDevice() throws JNIException;

    public static native void shutdownDevice() throws JNIException;

    public static native Set<Pin> getNotSupportedPins();
    public static native Set<I2CBus> getNotSupportedI2CBusses();

}
