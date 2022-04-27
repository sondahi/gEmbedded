package com.comert.gEmbedded.pi.device.i2c.command;

import com.comert.gEmbedded.api.device.common.exception.I2CMasterConfigurationException;
import com.comert.gEmbedded.api.device.common.exception.JNIException;
import com.comert.gEmbedded.api.device.common.exception.PinConfigurationException;
import com.comert.gEmbedded.api.device.i2c.impl.I2CMasterImpl;
import com.comert.gEmbedded.api.device.i2c.master.configurator.I2CMasterConfigurator;

// validate bus, and altenates are true

public class I2CMasterBusAndPinNumberValidatorProxy implements I2CMasterCreator {

    private final I2CMasterCreator I2CMasterCreatorContext = new I2CMasterCreatorContext();

    @Override
    public I2CMasterImpl createI2CMaster(I2CMasterConfigurator I2CMasterConfigurator) throws I2CMasterConfigurationException, PinConfigurationException, JNIException {

        return I2CMasterCreatorContext.createI2CMaster(I2CMasterConfigurator);

    }
}
