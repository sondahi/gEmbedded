package com.comert.gEmbedded.pi.device.gpio.command;

import com.comert.gEmbedded.pi.device.configurator.ConfigurationVisitor;
import com.comert.gEmbedded.pi.device.gpio.pin.DigitalInputPin;
import com.comert.gEmbedded.api.device.exception.JNIException;
import com.comert.gEmbedded.api.device.exception.PinConfigurationException;
import com.comert.gEmbedded.api.device.gpio.impl.InPutPinImpl;
import com.comert.gEmbedded.api.device.gpio.pin.configurator.InPutPinConfigurator;

public class AnalogInPutPinCommand extends PinCommandAdapter {

    @Override
    public InPutPinImpl createInPutPin(InPutPinConfigurator inPutPinConfigurator) throws JNIException, PinConfigurationException {
        ConfigurationVisitor configurationVisitor = ConfigurationVisitor.getInstance();
        configurationVisitor.accept(inPutPinConfigurator);
        return new DigitalInputPin(inPutPinConfigurator);
    }
}
