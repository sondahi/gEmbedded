package com.comert.gEmbedded.pi.device.gpio.command;

import com.comert.gEmbedded.api.device.exception.JNIException;
import com.comert.gEmbedded.api.device.exception.PinConfigurationException;
import com.comert.gEmbedded.api.device.exception.ProviderException;
import com.comert.gEmbedded.api.device.gpio.impl.InPutPinImpl;
import com.comert.gEmbedded.api.device.gpio.impl.OutPutPinImpl;
import com.comert.gEmbedded.api.device.gpio.impl.PWMPinImpl;
import com.comert.gEmbedded.api.device.gpio.pin.PWMType;
import com.comert.gEmbedded.api.device.gpio.pin.configurator.InPutPinConfigurator;
import com.comert.gEmbedded.api.device.gpio.pin.configurator.OutPutPinConfigurator;
import com.comert.gEmbedded.api.device.gpio.pin.configurator.PWMPinConfigurator;

public class PinCreatorContext implements PinCreator {

    private final PinCreator digitalInputPinCommand = new DigitalInPutPinCommand();
    private final PinCreator digitalOutPutPinCommand = new DigitalOutPutPinCommand();
    private final PinCreator softwarePWMPinCommand = new SoftwarePWMPinCommand();
    private final PinCreator hardwarePWMPinCommand = new HardwarePWMPinCommand();

    @Override
    public InPutPinImpl createInPutPin(InPutPinConfigurator inPutPinConfigurator) throws ProviderException, PinConfigurationException, JNIException {
            return digitalInputPinCommand.createInPutPin(inPutPinConfigurator);
    }

    @Override
    public OutPutPinImpl createOutPutPin(OutPutPinConfigurator outPutPinConfigurator) throws PinConfigurationException, ProviderException, JNIException {
        return digitalOutPutPinCommand.createOutPutPin(outPutPinConfigurator);
    }

    @Override
    public PWMPinImpl createPWMPin(PWMPinConfigurator PWMPinConfigurator) throws PinConfigurationException, ProviderException, JNIException {
        if (PWMPinConfigurator.getPWMType() == PWMType.SOFTWARE) {
            return softwarePWMPinCommand.createPWMPin(PWMPinConfigurator);
        } else {
            return hardwarePWMPinCommand.createPWMPin(PWMPinConfigurator);
        }
    }
}
