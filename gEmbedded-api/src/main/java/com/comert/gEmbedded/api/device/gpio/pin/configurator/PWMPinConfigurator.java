package com.comert.gEmbedded.api.device.gpio.pin.configurator;

import com.comert.gEmbedded.api.device.gpio.pin.PWMType;
import com.comert.gEmbedded.api.device.gpio.pin.Pin;
import com.comert.gEmbedded.api.device.gpio.pin.PinFunction;

public interface PWMPinConfigurator {

    interface PWMPinPWMTypeConfigurator {
        SoftwarePWMPinPropertyConfigurator softwarePWM();
        HardwarePWMPinPropertyConfigurator hardwarePWM();
    }

    static PWMPinPWMTypeConfigurator getBuilder() {
        return new PWMPinConfiguratorImpl.PWMPinPWMTypeConfiguratorImpl();
    }


    interface SoftwarePWMPinPropertyConfigurator {
        SoftwarePWMPinPropertyConfigurator pin(Pin pin);
        PWMPinConfigurator build();
    }

    interface HardwarePWMPinPropertyConfigurator {
        HardwarePWMPinPropertyConfigurator pin(Pin pin);
        PWMPinConfigurator build();
    }

    Pin getPin();

    PinFunction getPinFunction();

    PWMType getPWMType();

}
