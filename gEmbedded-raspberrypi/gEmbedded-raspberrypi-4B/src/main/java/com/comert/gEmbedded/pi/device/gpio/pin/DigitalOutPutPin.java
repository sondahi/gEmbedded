package com.comert.gEmbedded.pi.device.gpio.pin;

import com.comert.gEmbedded.api.device.common.exception.ExceptionMessage;
import com.comert.gEmbedded.api.device.common.exception.InstanceIsNotCreatedException;
import com.comert.gEmbedded.api.device.gpio.impl.OutPutPinImpl;
import com.comert.gEmbedded.api.device.gpio.pin.OutPutPin;
import com.comert.gEmbedded.api.device.gpio.pin.Pin;
import com.comert.gEmbedded.api.device.gpio.pin.configurator.OutPutPinConfigurator;
import com.comert.gEmbedded.pi.nativeinterface.GPIOController;

import java.util.HashMap;
import java.util.Map;

public final class DigitalOutPutPin extends OutPutPinImpl {

    private static final Map<Pin, OutPutPin> createdDigitalOutPutPins = new HashMap<>();

    private final Pin pin;

    private final int registerSelector;
    private final int pinSet;

    public DigitalOutPutPin(OutPutPinConfigurator outPutPinConfigurator) {
        pin = outPutPinConfigurator.getPin();

        registerSelector = (pin.getDigit() / 32);
        pinSet = (1 << (pin.getDigit() % 32));

        createdDigitalOutPutPins.put(pin, this);

        if (outPutPinConfigurator.getInitialState().getDigit() == 1) {
            GPIOController.write(registerSelector, pinSet);
        } else {
            GPIOController.clear(registerSelector, pinSet);
        }
    }

    public OutPutPin getInstanceIfExist(Pin pin) {
        if (createdDigitalOutPutPins.containsKey(pin)) {
            return createdDigitalOutPutPins.get(pin);
        } else {
            try {
                throw new InstanceIsNotCreatedException(ExceptionMessage.INSTANCE_IS_NOT_CREATED_MESSAGE, pin.getText());
            } catch (InstanceIsNotCreatedException InstanceIsNotCreatedException) {
                throw new RuntimeException(InstanceIsNotCreatedException.getMessage());
            }
        }
    }

    @Override
    public Pin getPin() {
        return pin;
    }

    @Override
    public void write() {
        GPIOController.write(registerSelector, pinSet);
    }

    @Override
    public void clear() {
        GPIOController.clear(registerSelector, pinSet);
    }

    @Override
    public boolean isLow() {
        return GPIOController.isLow(registerSelector, pinSet);
    }

    @Override
    public boolean isHigh() {
        return GPIOController.isHigh(registerSelector, pinSet);
    }

}
