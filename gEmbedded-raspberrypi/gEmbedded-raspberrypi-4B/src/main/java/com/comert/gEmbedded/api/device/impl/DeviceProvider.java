package com.comert.gEmbedded.api.device.impl;

import com.comert.gEmbedded.api.device.common.exception.JNIException;
import com.comert.gEmbedded.api.device.i2c.master.I2CBus;
import com.comert.gEmbedded.pi.nativeinterface.DeviceController;

public final class DeviceProvider extends DeviceImpl {

    private static final String JNI_EXCEPTION_CLASS = "com/comert/gEmbedded/api/device/common/exception/JNIException";
    private static final String MEMORY_FILE_NAME = "/dev/mem";
    private static final int PERIPHERAL_BASE_ADDRESS = 0xFE000000;
    private static final int GPIO_BASE_ADDRESS = PERIPHERAL_BASE_ADDRESS + 0x200000;
    private static final int GPIO_BLOCK_SIZE = 0xF4;
    private static final int BSC0_BASE_ADDRESS = PERIPHERAL_BASE_ADDRESS + 0x205000;
    private static final int BSC1_BASE_ADDRESS = PERIPHERAL_BASE_ADDRESS + 0x804000;
    private static final int BSC_BLOCK_SIZE = 0x20;

    public DeviceProvider() {
    }

    @Override
    protected void executeSetUp() {
        try {
            DeviceController.setUpJNIDriver(JNI_EXCEPTION_CLASS);
            DeviceController.setUpGpioDriver(MEMORY_FILE_NAME, GPIO_BASE_ADDRESS, GPIO_BLOCK_SIZE);
            DeviceController.setUpI2CMasterDriver(MEMORY_FILE_NAME, BSC0_BASE_ADDRESS, BSC_BLOCK_SIZE, I2CBus.BUS_0.getDigit());
            DeviceController.setUpI2CMasterDriver(MEMORY_FILE_NAME, BSC1_BASE_ADDRESS, BSC_BLOCK_SIZE, I2CBus.BUS_1.getDigit());
            deviceExecuting = true;
        } catch (JNIException jniException) {
            deviceExecuting = false;
            throw new RuntimeException(jniException.getMessage());
        }
    }

    @Override
    protected void executeShutDown() {
        try {
            DeviceController.shutDownI2CMasterDriver(BSC_BLOCK_SIZE, I2CBus.BUS_0.getDigit());
            DeviceController.shutDownI2CMasterDriver(BSC_BLOCK_SIZE, I2CBus.BUS_1.getDigit());
            DeviceController.shutDownGpioDriver(GPIO_BLOCK_SIZE);
            DeviceController.shutDownJNIDriver();
            deviceExecuting = false;
        } catch (JNIException jniException) {
            deviceExecuting = false;
            throw new RuntimeException(jniException.getMessage());
        }
    }

}
