package com.comert.gEmbedded.pi.device.gpio.pin;

import com.comert.gEmbedded.api.device.common.exception.ExceptionMessage;
import com.comert.gEmbedded.api.device.common.exception.InstanceIsNotCreatedException;
import com.comert.gEmbedded.api.device.gpio.impl.PWMPinImpl;
import com.comert.gEmbedded.api.device.gpio.pin.PWMPin;
import com.comert.gEmbedded.api.device.gpio.pin.PWMType;
import com.comert.gEmbedded.api.device.gpio.pin.Pin;
import com.comert.gEmbedded.api.device.gpio.pin.configurator.PWMPinConfigurator;
import com.comert.gEmbedded.pi.nativeinterface.GPIOController;

import java.util.HashMap;
import java.util.Map;

public final class SoftwarePWMPin extends PWMPinImpl {

    private static final Map<Pin, PWMPin> createdSoftwarePWMPins = new HashMap<>();

    private final Pin pin;
    private final PWMType pwmType;

    private final int registerSelector;
    private final int pinSet;

    public SoftwarePWMPin(PWMPinConfigurator pwmPinConfigurator) {
        pin = pwmPinConfigurator.getPin();
        pwmType = pwmPinConfigurator.getPWMType();

        this.registerSelector = (pin.getDigit() / 32);
        this.pinSet = (1 << (pin.getDigit() % 32));

        createdSoftwarePWMPins.put(pin, this);
    }

    @Override
    public PWMPin getInstanceIfExist(Pin pin) {
        if (createdSoftwarePWMPins.containsKey(pin)) {
            return createdSoftwarePWMPins.get(pin);
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
    public PWMType getPWMType() {
        return pwmType;
    }

    @Override
    public void pulse(final int periodInMicSec, int dutyCycleInMicSec) {
        GPIOController.pulse(registerSelector, pinSet, dutyCycleInMicSec, periodInMicSec - dutyCycleInMicSec);
    }

}
