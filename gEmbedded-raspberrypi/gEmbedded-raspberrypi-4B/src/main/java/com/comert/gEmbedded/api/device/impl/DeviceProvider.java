package com.comert.gEmbedded.api.device.impl;

import com.comert.gEmbedded.api.device.exception.JNIException;
import com.comert.gEmbedded.api.device.i2c.master.I2CBus;
import com.comert.gEmbedded.nativeinterface.DeviceController;

public final class DeviceProvider extends DeviceImpl {

    private static final String JNI_EXCEPTION_CLASS = "com/comert/gEmbedded/api/device/exception/JNIException";
    public DeviceProvider() {
    }

    @Override
    protected void executeSetUp() {
        try {
            DeviceController.setUpJNIDriver(JNI_EXCEPTION_CLASS);
            DeviceController.setUpGpioDriver();
            DeviceController.setUpI2CMasterDriver(I2CBus.BUS_0.getDigit());
            DeviceController.setUpI2CMasterDriver(I2CBus.BUS_1.getDigit());
        } catch (JNIException jniException) {
            throw new RuntimeException(jniException.getMessage());
        }
    }

    @Override
    protected void executeShutDown() {
        try {
            DeviceController.shutDownI2CMasterDriver(I2CBus.BUS_0.getDigit());
            DeviceController.shutDownI2CMasterDriver(I2CBus.BUS_1.getDigit());
            DeviceController.shutDownGpioDriver();
            DeviceController.shutDownJNIDriver();
        } catch (JNIException jniException) {
            throw new RuntimeException(jniException.getMessage());
        }
    }

}
