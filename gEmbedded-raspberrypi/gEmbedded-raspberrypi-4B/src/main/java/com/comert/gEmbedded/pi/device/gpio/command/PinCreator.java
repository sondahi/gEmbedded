package com.comert.gEmbedded.pi.device.gpio.command;

import com.comert.gEmbedded.api.device.common.exception.JNIException;
import com.comert.gEmbedded.api.device.common.exception.PinConfigurationException;
import com.comert.gEmbedded.api.device.common.exception.ProviderException;
import com.comert.gEmbedded.api.device.gpio.impl.InPutPinImpl;
import com.comert.gEmbedded.api.device.gpio.impl.OutPutPinImpl;
import com.comert.gEmbedded.api.device.gpio.impl.PWMPinImpl;
import com.comert.gEmbedded.api.device.gpio.pin.configurator.InPutPinConfigurator;
import com.comert.gEmbedded.api.device.gpio.pin.configurator.OutPutPinConfigurator;
import com.comert.gEmbedded.api.device.gpio.pin.configurator.PWMPinConfigurator;

public interface PinCreator {

    InPutPinImpl createInPutPin(InPutPinConfigurator inPutPinConfigurator) throws PinConfigurationException, ProviderException, JNIException;

    OutPutPinImpl createOutPutPin(OutPutPinConfigurator outPutPinConfigurator) throws PinConfigurationException, ProviderException, JNIException;

    PWMPinImpl createPWMPin(PWMPinConfigurator PWMPinConfigurator) throws PinConfigurationException, ProviderException, JNIException;

}
