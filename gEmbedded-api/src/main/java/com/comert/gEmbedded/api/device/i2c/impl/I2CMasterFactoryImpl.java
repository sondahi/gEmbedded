package com.comert.gEmbedded.api.device.i2c.impl;

import com.comert.gEmbedded.api.device.common.exception.InstanceCreationException;
import com.comert.gEmbedded.api.device.common.validator.InstanceCreationValidator;
import com.comert.gEmbedded.api.device.i2c.factory.I2CMasterFactory;
import com.comert.gEmbedded.api.device.i2c.master.I2CMaster;
import com.comert.gEmbedded.api.device.i2c.master.configurator.I2CMasterConfigurator;

public abstract class I2CMasterFactoryImpl implements I2CMasterFactory {

    protected I2CMasterFactoryImpl() {
        synchronized (this) {
            final var desiredFactoryClassName = "com.comert.gEmbedded.api.device.impl.DeviceImpl";
            try {
                InstanceCreationValidator.validateIfInstanceIsBeingCreatedInDesiredClass(desiredFactoryClassName);
            } catch (InstanceCreationException instanceCreationException) {
                throw new RuntimeException(instanceCreationException.getMessage());
            }
        }
    }

    /*
        Template Method pattern
    */
    @Override
    public final I2CMaster createI2CMaster(I2CMasterConfigurator I2CMasterConfigurator) {
        return _createI2Master(I2CMasterConfigurator);
    }

    protected abstract I2CMasterImpl _createI2Master(I2CMasterConfigurator I2CMasterConfigurator);
}
