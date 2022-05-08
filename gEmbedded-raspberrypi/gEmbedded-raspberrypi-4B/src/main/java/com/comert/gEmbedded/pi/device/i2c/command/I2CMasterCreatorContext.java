package com.comert.gEmbedded.pi.device.i2c.command;

import com.comert.gEmbedded.api.device.exception.I2CMasterConfigurationException;
import com.comert.gEmbedded.api.device.exception.JNIException;
import com.comert.gEmbedded.api.device.exception.PinConfigurationException;
import com.comert.gEmbedded.api.device.i2c.impl.I2CMasterImpl;
import com.comert.gEmbedded.api.device.i2c.master.I2CBus;
import com.comert.gEmbedded.api.device.i2c.master.configurator.I2CMasterConfigurator;

public class I2CMasterCreatorContext implements I2CMasterCreator {

    private final I2CMasterCreator I2CMasterZeroCommand = new I2CMasterZeroCommand();
    private final I2CMasterCreator I2CMasterOneCommand = new I2CMasterOneCommand();

    @Override
    public I2CMasterImpl createI2CMaster(I2CMasterConfigurator I2CMasterConfigurator) throws I2CMasterConfigurationException, PinConfigurationException, JNIException {

        if (I2CMasterConfigurator.getBus() == I2CBus.BUS_0) {
            return I2CMasterZeroCommand.createI2CMaster(I2CMasterConfigurator);
        } else {
            return I2CMasterOneCommand.createI2CMaster(I2CMasterConfigurator);
        }

    }
}
