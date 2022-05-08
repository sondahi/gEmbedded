package com.comert.gEmbedded.api.i2c.impl;

import com.comert.gEmbedded.api.device.exception.I2CMasterConfigurationException;
import com.comert.gEmbedded.api.device.exception.JNIException;
import com.comert.gEmbedded.api.device.exception.PinConfigurationException;
import com.comert.gEmbedded.api.device.i2c.impl.I2CMasterFactoryImpl;
import com.comert.gEmbedded.api.device.i2c.impl.I2CMasterImpl;
import com.comert.gEmbedded.api.device.i2c.master.configurator.I2CMasterConfigurator;
import com.comert.gEmbedded.pi.device.i2c.command.I2CMasterBusAndPinNumberValidatorProxy;
import com.comert.gEmbedded.pi.device.i2c.command.I2CMasterCreator;

public final class I2CMasterFactoryProvider extends I2CMasterFactoryImpl {

    private final I2CMasterCreator I2CMasterBusAndPinNumberValidatorProxy = new I2CMasterBusAndPinNumberValidatorProxy();

    @Override
    protected I2CMasterImpl _createI2Master(I2CMasterConfigurator I2CMasterConfigurator) {
        try {
            return I2CMasterBusAndPinNumberValidatorProxy.createI2CMaster(I2CMasterConfigurator);
        } catch (I2CMasterConfigurationException | PinConfigurationException | JNIException exception) {
            throw new RuntimeException(exception.getMessage());
        }
    }


}
