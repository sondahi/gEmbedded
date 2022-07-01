package com.comert.gEmbedded.nativeinterface;

import com.comert.gEmbedded.nativeinterface.util.NativeUtils;

import java.io.IOException;

public final class DeviceDriver {

    static {
        //System.loadLibrary("gEmbeddedRaspi4B32");
        try {
            NativeUtils.loadLibraryFromJar("/libgEmbeddedRaspi4B32.so");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private DeviceDriver() {
    }

    public synchronized native void setupDevice();

    public synchronized native void shutdownDevice();


}
