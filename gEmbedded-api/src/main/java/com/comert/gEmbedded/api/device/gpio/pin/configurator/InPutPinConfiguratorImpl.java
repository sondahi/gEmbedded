package com.comert.gEmbedded.api.device.gpio.pin.configurator;

import com.comert.gEmbedded.api.device.common.exception.ExceptionMessage;
import com.comert.gEmbedded.api.device.common.exception.PinConfigurationException;
import com.comert.gEmbedded.api.device.gpio.listener.GPIOEventListener;
import com.comert.gEmbedded.api.device.gpio.pin.*;

import java.util.StringJoiner;

// defaul values
final class InPutPinConfiguratorImpl implements InPutPinConfigurator {

    private final Pin pin;
    private final PinFunction pinFunction = PinFunction.INPUT;
    private final PinType pinType;
    private final PullUpDownStatus pullUpDownStatus;
    private final boolean eventConfigured;
    private final GPIOEventListener gpioEventListener;
    private final EventDetectStatus eventDetectStatus;
    private final int eventTimeout;

    public InPutPinConfiguratorImpl(Pin pin, PinType pinType, PullUpDownStatus pullUpDownStatus, boolean eventConfigured, GPIOEventListener gpioEventListener, EventDetectStatus eventDetectStatus, int eventTimeout) {

        if (pin == null) {
            try {
                throw new PinConfigurationException(ExceptionMessage.PIN_FIELD_IS_NOT_VALID_MESSAGE, "pin");
            } catch (PinConfigurationException pinConfigurationException) {
                throw new RuntimeException(pinConfigurationException.getMessage());
            }
        }

        if (pinType == null) {
            try {
                throw new PinConfigurationException(ExceptionMessage.PIN_FIELD_IS_NOT_VALID_MESSAGE, "pinType");
            } catch (PinConfigurationException pinConfigurationException) {
                throw new RuntimeException(pinConfigurationException.getMessage());
            }
        }

        if (pullUpDownStatus == null) {
            try {
                throw new PinConfigurationException(ExceptionMessage.PIN_FIELD_IS_NOT_VALID_MESSAGE, "pullUpDownStatus");
            } catch (PinConfigurationException pinConfigurationException) {
                throw new RuntimeException(pinConfigurationException.getMessage());
            }
        }

        if (eventConfigured) {
            if (gpioEventListener == null | eventDetectStatus == null | eventTimeout < 0) {
                String message = "";
                if (gpioEventListener == null) {
                    message += " gpioEventListener ";
                }
                if (eventDetectStatus == null) {
                    message += " eventDetectStatus ";
                }
                if (eventTimeout < 0) {
                    message += " eventTimeout ";
                }
                try {
                    throw new PinConfigurationException(ExceptionMessage.PIN_FIELD_IS_NOT_VALID_MESSAGE, message.trim());
                } catch (PinConfigurationException pinConfigurationException) {
                    throw new RuntimeException(pinConfigurationException.getMessage());
                }
            }
        }

        this.pin = pin;
        this.pinType = pinType;
        this.pullUpDownStatus = pullUpDownStatus;
        this.eventConfigured = eventConfigured;
        this.gpioEventListener = gpioEventListener;
        this.eventDetectStatus = eventDetectStatus;
        this.eventTimeout = eventTimeout;

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
    public PinType getPinType() {
        return pinType;
    }

    @Override
    public PullUpDownStatus getPullUpDownStatus() {
        return pullUpDownStatus;
    }

    @Override
    public boolean isEventConfigured() {
        return eventConfigured;
    }

    @Override
    public GPIOEventListener getEventListener() {
        return gpioEventListener;
    }

    @Override
    public EventDetectStatus getEventDetectStatus() {
        return eventDetectStatus;
    }

    @Override
    public int getEventTimeout() {
        return eventTimeout;
    }

    static class InPutPinPinConfiguratorImpl implements InPutPinPinConfigurator {

        @Override
        public InPutPinPropertyConfigurator pin(Pin pin) {
            return new InPutPinPropertyConfiguratorImpl(pin);
        }
    }

    private static class InPutPinPropertyConfiguratorImpl implements InPutPinPropertyConfigurator {

        private final Pin pin;
        private PinType pinType;
        private PullUpDownStatus pullUpDownStatus;
        private volatile boolean eventConfigured;
        private GPIOEventListener gpioEventListener;
        private EventDetectStatus eventDetectStatus;
        private int eventTimeout;

        private InPutPinPropertyConfiguratorImpl(Pin pin) {
            this.pin = pin;
        }

        @Override
        public InPutPinPropertyConfigurator pinType(PinType pinType) {
            this.pinType = pinType;
            return this;
        }

        @Override
        public InPutPinPropertyConfigurator pullUpDownStatus(PullUpDownStatus pullUpDownStatus) {
            this.pullUpDownStatus = pullUpDownStatus;
            return this;
        }

        @Override
        public InPutPinPropertyConfigurator eventStatus(GPIOEventListener gpioEventListener, EventDetectStatus eventDetectStatus, int timeoutInMilSec) {
            this.gpioEventListener = gpioEventListener;
            this.eventDetectStatus = eventDetectStatus;
            this.eventTimeout = timeoutInMilSec;
            this.eventConfigured = true;
            return this;
        }

        public InPutPinConfigurator build() {
            return new InPutPinConfiguratorImpl(pin, pinType, pullUpDownStatus, eventConfigured, gpioEventListener, eventDetectStatus, eventTimeout);
        }

    }

    @Override
    public String toString() {
        return new StringJoiner(", ", InPutPinConfiguratorImpl.class.getSimpleName() + "[", "]")
                .add("pin=" + pin)
                .add("pinFunction=" + pinFunction)
                .add("pinType=" + pinType)
                .add("pullUpDownStatus=" + pullUpDownStatus)
                .add("eventConfigured=" + eventConfigured)
                .add("gpioEventListener=" + gpioEventListener)
                .add("eventDetectStatus=" + eventDetectStatus)
                .add("eventTimeout=" + eventTimeout)
                .toString();
    }

}
