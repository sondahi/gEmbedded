package com.comert.gEmbedded.pi.device.gpio.command;

import com.comert.gEmbedded.api.device.common.exception.ExceptionMessage;
import com.comert.gEmbedded.api.device.common.exception.JNIException;
import com.comert.gEmbedded.api.device.common.exception.PinConfigurationException;
import com.comert.gEmbedded.api.device.common.exception.ProviderException;
import com.comert.gEmbedded.api.device.gpio.impl.InPutPinImpl;
import com.comert.gEmbedded.api.device.gpio.impl.OutPutPinImpl;
import com.comert.gEmbedded.api.device.gpio.impl.PWMPinImpl;
import com.comert.gEmbedded.api.device.gpio.pin.PinType;
import com.comert.gEmbedded.api.device.gpio.pin.configurator.InPutPinConfigurator;
import com.comert.gEmbedded.api.device.gpio.pin.configurator.OutPutPinConfigurator;
import com.comert.gEmbedded.api.device.gpio.pin.configurator.PWMPinConfigurator;

public class PinTypeValidatorProxy implements PinCreator {

    private final PinCreator pinCreatorContext = new PinCreatorContext();

    @Override
    public InPutPinImpl createInPutPin(InPutPinConfigurator inPutPinConfigurator) throws PinConfigurationException, ProviderException, JNIException {
        switch (inPutPinConfigurator.getPinType()) {
            case DIGITAL: {
                return pinCreatorContext.createInPutPin(inPutPinConfigurator);
            }
            default: {
                throw new PinConfigurationException(ExceptionMessage.PIN_TYPE_IS_NOT_SUPPORTED_MESSAGE, PinType.ANALOG.getText());
            }
        }

    }

    @Override
    public OutPutPinImpl createOutPutPin(OutPutPinConfigurator outPutPinConfigurator) throws PinConfigurationException, ProviderException, JNIException {
        return pinCreatorContext.createOutPutPin(outPutPinConfigurator);
    }

    @Override
    public PWMPinImpl createPWMPin(PWMPinConfigurator PWMPinConfigurator) throws PinConfigurationException, ProviderException, JNIException {

        return pinCreatorContext.createPWMPin(PWMPinConfigurator);

    }
}
