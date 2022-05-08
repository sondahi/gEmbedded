package com.comert.gEmbedded.pi.device.i2c.command;

import com.comert.gEmbedded.pi.device.configurator.ConfigurationVisitor;
import com.comert.gEmbedded.api.device.exception.I2CMasterConfigurationException;
import com.comert.gEmbedded.api.device.exception.JNIException;
import com.comert.gEmbedded.api.device.exception.PinConfigurationException;
import com.comert.gEmbedded.api.device.i2c.impl.I2CMasterImpl;
import com.comert.gEmbedded.api.device.i2c.master.configurator.I2CMasterConfigurator;
import com.comert.gEmbedded.pi.device.i2c.master.I2CMasterZero;

public class I2CMasterZeroCommand implements I2CMasterCreator {

    @Override
    public I2CMasterImpl createI2CMaster(I2CMasterConfigurator i2CMasterConfigurator) throws JNIException, PinConfigurationException, I2CMasterConfigurationException {
        ConfigurationVisitor configurationVisitor = ConfigurationVisitor.getInstance();
        configurationVisitor.accept(i2CMasterConfigurator);
        return new I2CMasterZero(i2CMasterConfigurator);
    }
}
