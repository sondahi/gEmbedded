package com.comert.gEmbedded.api.device.i2c.master.configurator;

import com.comert.gEmbedded.api.device.gpio.pin.PinFunction;
import com.comert.gEmbedded.api.device.gpio.pin.Pin;
import com.comert.gEmbedded.api.device.i2c.master.I2CBus;

public interface I2CMasterConfigurator {

    interface I2CMasterBusNumberConfigurator {
        I2CMasterPropertyConfigurator bus(I2CBus i2CBus);
    }

    static I2CMasterBusNumberConfigurator getBuilder() {
        return new I2CMasterConfiguratorImpl.I2CMasterBusNumberConfiguratorImpl();
    }

    interface I2CMasterPropertyConfigurator {

        I2CMasterPropertyConfigurator sdaPin(Pin sdaPin, PinFunction sdaPinFunction);

        I2CMasterPropertyConfigurator sclPin(Pin sclPin, PinFunction sclPinFunction);

        I2CMasterPropertyConfigurator busClockInHertz(int busClockInHertz);

        I2CMasterPropertyConfigurator busClockStretchTimeout(int busClockStretchTimeout);

        I2CMasterConfigurator build();

    }

    I2CBus getBus();

    Pin getSDAPin();

    PinFunction getSDAPinFunction();

    Pin getSCLPin();

    PinFunction getSCLPinFunction();

    int getBusClockInHertz();

    int getBusClockStretchTimeout();


}
