package com.comert.gEmbedded.api.device.impl;

import com.comert.gEmbedded.api.device.exception.JNIException;
import com.comert.gEmbedded.nativeinterface.DeviceDriver;

public final class DeviceProvider extends DeviceImpl {
    public DeviceProvider() {
    }

    @Override
    protected void executeSetUp() {
        try {
            DeviceDriver.setupDevice();
        } catch (JNIException jniException) {
            throw new RuntimeException(jniException.getMessage());
        }
    }

    @Override
    protected void executeShutDown() {
        try {
            DeviceDriver.shutdownDevice();
        } catch (JNIException jniException) {
            throw new RuntimeException(jniException.getMessage());
        }
    }

}
