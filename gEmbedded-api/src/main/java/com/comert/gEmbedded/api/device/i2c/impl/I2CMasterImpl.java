package com.comert.gEmbedded.api.device.i2c.impl;

import com.comert.gEmbedded.api.device.common.exception.InstanceCreationException;
import com.comert.gEmbedded.api.device.common.validator.InstanceCreationValidator;
import com.comert.gEmbedded.api.device.i2c.master.I2CMaster;

public abstract class I2CMasterImpl implements I2CMaster {

    protected I2CMasterImpl() {
        synchronized (this) {
            final var desiredFactoryClassName = "com.comert.gEmbedded.api.i2c.impl.I2CMasterFactoryProvider";
            try {
                InstanceCreationValidator.validateIfInstanceIsBeingCreatedInDesiredClass(desiredFactoryClassName);
            } catch (InstanceCreationException instanceCreationException) {
                throw new RuntimeException(instanceCreationException.getMessage());
            }
        }
    }

}
