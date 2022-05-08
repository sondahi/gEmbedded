package com.comert.gEmbedded.pi.device.i2c.command;

import com.comert.gEmbedded.api.device.exception.I2CMasterConfigurationException;
import com.comert.gEmbedded.api.device.exception.JNIException;
import com.comert.gEmbedded.api.device.exception.PinConfigurationException;
import com.comert.gEmbedded.api.device.i2c.impl.I2CMasterImpl;
import com.comert.gEmbedded.api.device.i2c.master.configurator.I2CMasterConfigurator;

public interface I2CMasterCreator {

    I2CMasterImpl createI2CMaster(I2CMasterConfigurator I2CMasterConfigurator) throws I2CMasterConfigurationException, PinConfigurationException, JNIException;

}
