package com.comert.gEmbedded.api.device;

import com.comert.gEmbedded.api.device.gpio.factory.GPIOFactory;
import com.comert.gEmbedded.api.device.i2c.factory.I2CMasterFactory;

public interface Device {

    void setUpDevice();

    void shutDownDevice();

    GPIOFactory getGPIOFactoryInstance();

    I2CMasterFactory getI2CMasterFactoryInstance();

}
