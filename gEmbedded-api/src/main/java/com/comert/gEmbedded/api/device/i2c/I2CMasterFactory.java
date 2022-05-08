package com.comert.gEmbedded.api.device.i2c;

import com.comert.gEmbedded.api.device.i2c.master.I2CMaster;
import com.comert.gEmbedded.api.device.i2c.master.configurator.I2CMasterConfigurator;

public interface I2CMasterFactory {

    I2CMaster createI2CMaster(I2CMasterConfigurator I2CMasterConfigurator);

}
