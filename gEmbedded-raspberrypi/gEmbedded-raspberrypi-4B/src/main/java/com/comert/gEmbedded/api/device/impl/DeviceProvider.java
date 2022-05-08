package com.comert.gEmbedded.api.device.impl;

import com.comert.gEmbedded.api.device.exception.JNIException;
import com.comert.gEmbedded.nativeinterface.DeviceController;

public final class DeviceProvider extends DeviceImpl {
    public DeviceProvider() {
    }

    @Override
    protected void executeSetUp() {
        try {
            DeviceController.setupDevice();
        } catch (JNIException jniException) {
            throw new RuntimeException(jniException.getMessage());
        }
    }

    @Override
    protected void executeShutDown() {
        try {
            DeviceController.shutdownDevice();
        } catch (JNIException jniException) {
            throw new RuntimeException(jniException.getMessage());
        }
    }

}
