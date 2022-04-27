package com.comert.gEmbedded.api.device.gpio.impl;

import com.comert.gEmbedded.api.device.common.exception.InstanceCreationException;
import com.comert.gEmbedded.api.device.common.validator.InstanceCreationValidator;
import com.comert.gEmbedded.api.device.gpio.factory.GPIOFactory;
import com.comert.gEmbedded.api.device.gpio.pin.InPutPin;
import com.comert.gEmbedded.api.device.gpio.pin.PWMPin;
import com.comert.gEmbedded.api.device.gpio.pin.configurator.InPutPinConfigurator;
import com.comert.gEmbedded.api.device.gpio.pin.OutPutPin;
import com.comert.gEmbedded.api.device.gpio.pin.configurator.OutPutPinConfigurator;
import com.comert.gEmbedded.api.device.gpio.pin.configurator.PWMPinConfigurator;

public abstract class GPIOFactoryImpl implements GPIOFactory {

    protected GPIOFactoryImpl() {
        synchronized (this) {
            final var desiredFactoryClassName = "com.comert.gEmbedded.api.device.impl.DeviceImpl";
            try {
                InstanceCreationValidator.validateIfInstanceIsBeingCreatedInDesiredClass(desiredFactoryClassName);
            } catch (InstanceCreationException instanceCreationException) {
                throw new RuntimeException(instanceCreationException.getMessage());
            }
        }
    }

    /*
        Template Method pattern
    */
    @Override
    public final InPutPin createInPutPin(InPutPinConfigurator inPutPinConfigurator) {
        return _createInPutPin(inPutPinConfigurator);
    }

    /*
        Template Method pattern
    */
    @Override
    public final OutPutPin createOutPutPin(OutPutPinConfigurator outPutPinConfigurator) {
        return _createOutPutPin(outPutPinConfigurator);
    }

    /*
        Template Method pattern
    */
    @Override
    public final PWMPin createPWMPin(PWMPinConfigurator PWMPinConfigurator) {
        return _createPWMPin(PWMPinConfigurator);
    }

    protected abstract InPutPinImpl _createInPutPin(InPutPinConfigurator inPutPinConfigurator);

    protected abstract OutPutPinImpl _createOutPutPin(OutPutPinConfigurator outPutPinConfigurator);

    protected abstract PWMPinImpl _createPWMPin(PWMPinConfigurator PWMPinConfigurator);

}
