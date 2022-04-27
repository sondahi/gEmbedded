package com.comert.gEmbedded.api.device.impl;

import org.junit.jupiter.api.Disabled;

@Disabled
public class DeviceProvider extends DeviceImpl {
    @Override
    protected void executeSetUp() {
        System.out.println("Test DeviceProvider executing setup");
    }

    @Override
    protected void executeShutDown() {
        System.out.println("Test DeviceProvider executing shutdown");
    }
}
