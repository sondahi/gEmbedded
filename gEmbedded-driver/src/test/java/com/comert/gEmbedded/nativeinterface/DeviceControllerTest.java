package com.comert.gEmbedded.nativeinterface;

import com.comert.gEmbedded.api.device.exception.JNIException;

class DeviceControllerTest {

    @org.junit.jupiter.api.Test
    void setupDevice() {
        try {
            DeviceController.setupDevice();
        } catch (JNIException | RuntimeException e) {
            e.printStackTrace();
            System.out.println("Hello World");
        }
    }
}