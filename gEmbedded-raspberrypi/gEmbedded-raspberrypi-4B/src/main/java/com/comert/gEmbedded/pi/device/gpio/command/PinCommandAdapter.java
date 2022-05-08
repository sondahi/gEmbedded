package com.comert.gEmbedded.pi.device.gpio.command;

import com.comert.gEmbedded.api.device.exception.ExceptionMessage;
import com.comert.gEmbedded.api.device.exception.JNIException;
import com.comert.gEmbedded.api.device.exception.PinConfigurationException;
import com.comert.gEmbedded.api.device.exception.ProviderException;
import com.comert.gEmbedded.api.device.gpio.impl.InPutPinImpl;
import com.comert.gEmbedded.api.device.gpio.impl.OutPutPinImpl;
import com.comert.gEmbedded.api.device.gpio.impl.PWMPinImpl;
import com.comert.gEmbedded.api.device.gpio.pin.configurator.InPutPinConfigurator;
import com.comert.gEmbedded.api.device.gpio.pin.configurator.OutPutPinConfigurator;
import com.comert.gEmbedded.api.device.gpio.pin.configurator.PWMPinConfigurator;

public abstract class PinCommandAdapter implements PinCreator {

    @Override
    public InPutPinImpl createInPutPin(InPutPinConfigurator inPutPinConfigurator) throws ProviderException, JNIException, PinConfigurationException {
        throw new ProviderException(ExceptionMessage.PROVIDER_DOES_NOT_IMPLEMENT_INTERFACE_METHOD_MESSAGE, "public InPutPin createInPutPin(InPutPinConfigurator inPutPinConfigurator)");
    }

    @Override
    public OutPutPinImpl createOutPutPin(OutPutPinConfigurator outPutPinConfigurator) throws ProviderException, JNIException, PinConfigurationException {
        throw new ProviderException(ExceptionMessage.PROVIDER_DOES_NOT_IMPLEMENT_INTERFACE_METHOD_MESSAGE, "public OutPutPin createOutPutPin(OutPutPinConfigurator outPutPinConfigurator)");
    }

    @Override
    public PWMPinImpl createPWMPin(PWMPinConfigurator PWMPinConfigurator) throws ProviderException, JNIException, PinConfigurationException {
        throw new ProviderException(ExceptionMessage.PROVIDER_DOES_NOT_IMPLEMENT_INTERFACE_METHOD_MESSAGE, "public PWMPin createPWMPin(PWMPinConfigurator PWMPinConfigurator)");
    }

}
