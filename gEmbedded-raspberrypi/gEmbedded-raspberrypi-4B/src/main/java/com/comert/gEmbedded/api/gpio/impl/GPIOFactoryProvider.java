package com.comert.gEmbedded.api.gpio.impl;

import com.comert.gEmbedded.api.device.common.exception.JNIException;
import com.comert.gEmbedded.api.device.common.exception.PinConfigurationException;
import com.comert.gEmbedded.api.device.common.exception.ProviderException;
import com.comert.gEmbedded.api.device.gpio.impl.GPIOFactoryImpl;
import com.comert.gEmbedded.api.device.gpio.impl.InPutPinImpl;
import com.comert.gEmbedded.api.device.gpio.impl.OutPutPinImpl;
import com.comert.gEmbedded.api.device.gpio.impl.PWMPinImpl;
import com.comert.gEmbedded.api.device.gpio.pin.configurator.InPutPinConfigurator;
import com.comert.gEmbedded.api.device.gpio.pin.configurator.OutPutPinConfigurator;
import com.comert.gEmbedded.api.device.gpio.pin.configurator.PWMPinConfigurator;
import com.comert.gEmbedded.pi.device.gpio.command.PinCreator;
import com.comert.gEmbedded.pi.device.gpio.command.PinTypeValidatorProxy;


public final class GPIOFactoryProvider extends GPIOFactoryImpl {

    private final PinCreator pinTypeValidatorProxy = new PinTypeValidatorProxy();


    public GPIOFactoryProvider() {
    }

    @Override
    protected InPutPinImpl _createInPutPin(InPutPinConfigurator inPutPinConfigurator) {
        try {
            return pinTypeValidatorProxy.createInPutPin(inPutPinConfigurator);
        } catch (PinConfigurationException | ProviderException | JNIException exception) {
            throw new RuntimeException(exception.getMessage());
        }
    }

    @Override
    protected OutPutPinImpl _createOutPutPin(OutPutPinConfigurator outPutPinConfigurator) {
        try {
            return pinTypeValidatorProxy.createOutPutPin(outPutPinConfigurator);
        } catch (PinConfigurationException | ProviderException | JNIException exception) {
            throw new RuntimeException(exception.getMessage());
        }
    }

    @Override
    protected PWMPinImpl _createPWMPin(PWMPinConfigurator PWMPinConfigurator) {
        try {
            return pinTypeValidatorProxy.createPWMPin(PWMPinConfigurator);
        } catch (PinConfigurationException | ProviderException | JNIException exception) {
            throw new RuntimeException(exception.getMessage());
        }
    }


}
