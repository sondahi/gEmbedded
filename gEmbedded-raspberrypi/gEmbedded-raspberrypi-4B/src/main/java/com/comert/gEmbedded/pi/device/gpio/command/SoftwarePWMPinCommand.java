package com.comert.gEmbedded.pi.device.gpio.command;

import com.comert.gEmbedded.pi.device.configurator.ConfigurationVisitor;
import com.comert.gEmbedded.api.device.exception.JNIException;
import com.comert.gEmbedded.api.device.exception.PinConfigurationException;
import com.comert.gEmbedded.api.device.gpio.impl.PWMPinImpl;
import com.comert.gEmbedded.api.device.gpio.pin.configurator.PWMPinConfigurator;
import com.comert.gEmbedded.pi.device.gpio.pin.SoftwarePWMPin;

public class SoftwarePWMPinCommand extends PinCommandAdapter {

    @Override
    public PWMPinImpl createPWMPin(PWMPinConfigurator pwmPinConfigurator) throws JNIException, PinConfigurationException {
        ConfigurationVisitor configurationVisitor = ConfigurationVisitor.getInstance();
        configurationVisitor.accept(pwmPinConfigurator);
        return new SoftwarePWMPin(pwmPinConfigurator);
    }

}
