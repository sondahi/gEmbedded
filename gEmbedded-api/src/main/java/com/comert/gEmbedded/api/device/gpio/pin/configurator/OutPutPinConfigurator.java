package com.comert.gEmbedded.api.device.gpio.pin.configurator;

import com.comert.gEmbedded.api.device.gpio.pin.Pin;
import com.comert.gEmbedded.api.device.gpio.pin.PinFunction;
import com.comert.gEmbedded.api.device.gpio.pin.PinState;

public interface OutPutPinConfigurator {

    interface OutPutPinPropertyConfigurator {

        OutPutPinPropertyConfigurator pin(Pin pin);

        OutPutPinPropertyConfigurator initialState(PinState pinState);

        OutPutPinConfigurator build();

    }

    static OutPutPinPropertyConfigurator getBuilder() {
        return new OutPutPinConfiguratorImpl.OutPutPinPropertyConfiguratorImpl();
    }

    Pin getPin();

    PinFunction getPinFunction();

    PinState getInitialState();

}
