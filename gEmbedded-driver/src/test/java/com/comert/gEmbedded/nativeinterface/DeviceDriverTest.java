package com.comert.gEmbedded.nativeinterface;

import com.comert.gEmbedded.api.device.exception.JNIException;

class DeviceDriverTest {

    @org.junit.jupiter.api.Test
    void setupDevice() {
        try {
            DeviceDriver.setupDevice();
        } catch (JNIException | RuntimeException e) {
            e.printStackTrace();
            System.out.println("Hello World");
        }
    }
}