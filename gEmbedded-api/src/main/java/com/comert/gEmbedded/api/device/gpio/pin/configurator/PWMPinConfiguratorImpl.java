package com.comert.gEmbedded.api.device.gpio.pin.configurator;

import com.comert.gEmbedded.api.device.common.exception.ExceptionMessage;
import com.comert.gEmbedded.api.device.common.exception.PinConfigurationException;
import com.comert.gEmbedded.api.device.gpio.pin.PWMType;
import com.comert.gEmbedded.api.device.gpio.pin.Pin;
import com.comert.gEmbedded.api.device.gpio.pin.PinFunction;

import java.util.StringJoiner;

final class PWMPinConfiguratorImpl implements PWMPinConfigurator {

    private final Pin pin;
    private final PinFunction pinFunction = PinFunction.OUTPUT;
    private final PWMType pwmType;

    public PWMPinConfiguratorImpl(Pin pin, PWMType pwmType) {
        if (pin == null) {
            try {
                throw new PinConfigurationException(ExceptionMessage.PIN_FIELD_IS_NOT_VALID_MESSAGE, "pin");
            } catch (PinConfigurationException pinConfigurationException) {
                throw new RuntimeException(pinConfigurationException.getMessage());
            }
        }
        if (pwmType == null) {
            try {
                throw new PinConfigurationException(ExceptionMessage.PIN_FIELD_IS_NOT_VALID_MESSAGE, "pwmType");
            } catch (PinConfigurationException pinConfigurationException) {
                throw new RuntimeException(pinConfigurationException.getMessage());
            }
        }

        this.pin = pin;
        this.pwmType = pwmType;
    }

    @Override
    public Pin getPin() {
        return pin;
    }

    @Override
    public PinFunction getPinFunction() {
        return pinFunction;
    }

    @Override
    public PWMType getPWMType() {
        return pwmType;
    }

    static class PWMPinPWMTypeConfiguratorImpl implements PWMPinPWMTypeConfigurator {

        @Override
        public SoftwarePWMPinPropertyConfigurator softwarePWM() {
            return new SoftwarePWMPinPropertyConfiguratorImpl();
        }

        @Override
        public HardwarePWMPinPropertyConfigurator hardwarePWM() {
            return new HardwarePWMPinPropertyConfiguratorImpl();
        }
    }

    static class SoftwarePWMPinPropertyConfiguratorImpl implements SoftwarePWMPinPropertyConfigurator {

        private Pin pin;

        @Override
        public SoftwarePWMPinPropertyConfigurator pin(Pin pin) {
            this.pin = pin;
            return this;
        }

        @Override
        public PWMPinConfigurator build() {
            return new PWMPinConfiguratorImpl(pin, PWMType.SOFTWARE);
        }
    }

    static class HardwarePWMPinPropertyConfiguratorImpl implements HardwarePWMPinPropertyConfigurator {

        private Pin pin;

        @Override
        public HardwarePWMPinPropertyConfigurator pin(Pin pin) {
            this.pin = pin;
            return this;
        }

        @Override
        public PWMPinConfigurator build() {
            return new PWMPinConfiguratorImpl(pin, PWMType.HARDWARE);
        }
    }

    @Override
    public String toString() {
        return new StringJoiner(", ", PWMPinConfiguratorImpl.class.getSimpleName() + "[", "]")
                .add("pin=" + pin)
                .add("pinFunction=" + pinFunction)
                .add("pwmType=" + pwmType)
                .toString();
    }
}
