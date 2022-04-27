package com.comert.gEmbedded.api.device.gpio.pin.configurator;

import com.comert.gEmbedded.api.device.common.exception.ExceptionMessage;
import com.comert.gEmbedded.api.device.common.exception.PinConfigurationException;
import com.comert.gEmbedded.api.device.gpio.pin.Pin;
import com.comert.gEmbedded.api.device.gpio.pin.PinFunction;
import com.comert.gEmbedded.api.device.gpio.pin.PinState;

import java.util.StringJoiner;

final class OutPutPinConfiguratorImpl implements OutPutPinConfigurator {

    private final Pin pin;
    private final PinFunction pinFunction = PinFunction.OUTPUT;
    private final PinState initialState;

    public OutPutPinConfiguratorImpl(Pin pin, PinState initialState) {
        if (pin == null) {
            try {
                throw new PinConfigurationException(ExceptionMessage.PIN_FIELD_IS_NOT_VALID_MESSAGE, "pin");
            } catch (PinConfigurationException pinConfigurationException) {
                throw new RuntimeException(pinConfigurationException.getMessage());
            }
        }

        if (initialState == null) {
            try {
                throw new PinConfigurationException(ExceptionMessage.PIN_FIELD_IS_NOT_VALID_MESSAGE, "initialState");
            } catch (PinConfigurationException pinConfigurationException) {
                throw new RuntimeException(pinConfigurationException.getMessage());
            }
        }

        this.pin = pin;
        this.initialState = initialState;
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
    public PinState getInitialState() {
        return initialState;
    }

    static class OutPutPinPropertyConfiguratorImpl implements OutPutPinPropertyConfigurator {

        private Pin pin;
        private PinState initialState;

        public OutPutPinPropertyConfiguratorImpl() {
        }

        @Override
        public OutPutPinPropertyConfigurator pin(Pin pin) {
            this.pin = pin;
            return this;
        }

        @Override
        public OutPutPinPropertyConfigurator initialState(PinState initialState) {
            this.initialState = initialState;
            return this;
        }

        public OutPutPinConfigurator build() {
            return new OutPutPinConfiguratorImpl(pin, initialState);
        }



    }

    @Override
    public String toString() {
        return new StringJoiner(", ", OutPutPinConfiguratorImpl.class.getSimpleName() + "[", "]")
                .add("pin=" + pin)
                .add("pinFunction=" + pinFunction)
                .add("initialState=" + initialState)
                .toString();
    }

}
