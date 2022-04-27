package com.comert.gEmbedded.pi.device.gpio.command;

import com.comert.gEmbedded.pi.device.configurator.ConfigurationVisitor;
import com.comert.gEmbedded.api.device.common.exception.JNIException;
import com.comert.gEmbedded.api.device.common.exception.PinConfigurationException;
import com.comert.gEmbedded.api.device.gpio.impl.OutPutPinImpl;
import com.comert.gEmbedded.api.device.gpio.pin.configurator.OutPutPinConfigurator;
import com.comert.gEmbedded.pi.device.gpio.pin.DigitalOutPutPin;

public class DigitalOutPutPinCommand extends PinCommandAdapter {

    @Override
    public OutPutPinImpl createOutPutPin(OutPutPinConfigurator outPutPinConfigurator) throws JNIException, PinConfigurationException {
        ConfigurationVisitor configurationVisitor = ConfigurationVisitor.getInstance();
        configurationVisitor.accept(outPutPinConfigurator);
        return new DigitalOutPutPin(outPutPinConfigurator);
    }
}
