package com.comert.gEmbedded.api.device.gpio;

import com.comert.gEmbedded.api.device.gpio.pin.InPutPin;
import com.comert.gEmbedded.api.device.gpio.pin.PWMPin;
import com.comert.gEmbedded.api.device.gpio.pin.configurator.InPutPinConfigurator;
import com.comert.gEmbedded.api.device.gpio.pin.OutPutPin;
import com.comert.gEmbedded.api.device.gpio.pin.configurator.OutPutPinConfigurator;
import com.comert.gEmbedded.api.device.gpio.pin.configurator.PWMPinConfigurator;

public interface GPIOFactory {

    InPutPin createInPutPin(InPutPinConfigurator inPutPinConfigurator);

    OutPutPin createOutPutPin(OutPutPinConfigurator outPutPinConfigurator);

    PWMPin createPWMPin(PWMPinConfigurator PWMPinConfigurator);

}
