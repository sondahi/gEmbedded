package com.comert.gEmbedded.api.gpio.impl;

import com.comert.gEmbedded.api.device.gpio.pin.configurator.InPutPinConfigurator;
import com.comert.gEmbedded.api.device.gpio.impl.GPIOFactoryImpl;
import com.comert.gEmbedded.api.device.gpio.impl.InPutPinImpl;
import com.comert.gEmbedded.api.device.gpio.impl.OutPutPinImpl;
import com.comert.gEmbedded.api.device.gpio.impl.PWMPinImpl;
import com.comert.gEmbedded.api.device.gpio.pin.configurator.OutPutPinConfigurator;
import com.comert.gEmbedded.api.device.gpio.pin.configurator.PWMPinConfigurator;
import org.junit.jupiter.api.Disabled;

@Disabled
public class GPIOFactoryProvider extends GPIOFactoryImpl {


    @Override
    protected InPutPinImpl _createInPutPin(InPutPinConfigurator inPutPinConfigurator) {
        return null;
    }

    @Override
    protected OutPutPinImpl _createOutPutPin(OutPutPinConfigurator outPutPinConfigurator) {
        return null;
    }

    @Override
    protected PWMPinImpl _createPWMPin(PWMPinConfigurator PWMPinConfigurator) {
        return null;
    }
}
