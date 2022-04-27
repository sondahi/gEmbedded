package com.comert.gEmbedded.api.device.gpio.pin.configurator;

import com.comert.gEmbedded.api.device.gpio.listener.GPIOEventListener;
import com.comert.gEmbedded.api.device.gpio.pin.*;

public interface InPutPinConfigurator {

    interface InPutPinPinConfigurator {
        InPutPinPropertyConfigurator pin(Pin pin);
    }

    static InPutPinPinConfigurator getBuilder() {
        return new InPutPinConfiguratorImpl.InPutPinPinConfiguratorImpl();
    }

    interface InPutPinPropertyConfigurator {

        InPutPinPropertyConfigurator pinType(PinType pinType);

        InPutPinPropertyConfigurator pullUpDownStatus(PullUpDownStatus pullUpDownStatus);

        // for non-blocking timeout must be greater than 0 and maybe less than 1000 millisecond ?
        InPutPinPropertyConfigurator eventStatus(GPIOEventListener gpioEventListener, EventDetectStatus eventDetectStatus, int timeoutInMilSec);

        InPutPinConfigurator build();

    }

    Pin getPin();

    PinFunction getPinFunction();

    PinType getPinType();

    PullUpDownStatus getPullUpDownStatus();

    boolean isEventConfigured();

    GPIOEventListener getEventListener();

    EventDetectStatus getEventDetectStatus();

    int getEventTimeout();

}
