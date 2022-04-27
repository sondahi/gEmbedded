package com.comert.gEmbedded.api.device.i2c.master.configurator;

import com.comert.gEmbedded.api.device.common.exception.ExceptionMessage;
import com.comert.gEmbedded.api.device.common.exception.I2CMasterConfigurationException;
import com.comert.gEmbedded.api.device.gpio.pin.Pin;
import com.comert.gEmbedded.api.device.gpio.pin.PinFunction;
import com.comert.gEmbedded.api.device.i2c.master.I2CBus;

import java.util.StringJoiner;

public class I2CMasterConfiguratorImpl implements I2CMasterConfigurator {

    private final I2CBus i2CBus;
    private final Pin sdaPin;
    private final PinFunction sdaPinFunction;
    private final Pin sclPin;
    private final PinFunction sclPinFunction;
    private final int busClockInHertz;
    private final int busClockStretchTimout;

    public I2CMasterConfiguratorImpl(I2CBus i2CBus,
                                     Pin sdaPin,
                                     PinFunction sdaPinFunction,
                                     Pin sclPin,
                                     PinFunction sclPinFunction,
                                     int busClockInHertz,
                                     int busClockStretchTimout) {
        // refactor
        if (i2CBus == null) {
            try {
                throw new I2CMasterConfigurationException(ExceptionMessage.PIN_FIELD_IS_NOT_VALID_MESSAGE, "i2CBus");
            } catch (I2CMasterConfigurationException i2CMasterConfigurationException) {
                throw new RuntimeException(i2CMasterConfigurationException.getMessage());
            }
        }

        if (sdaPin == null) {
            try {
                throw new I2CMasterConfigurationException(ExceptionMessage.PIN_FIELD_IS_NOT_VALID_MESSAGE, "SDAPinNumber");
            } catch (I2CMasterConfigurationException i2CMasterConfigurationException) {
                throw new RuntimeException(i2CMasterConfigurationException.getMessage());
            }
        }

        if (sdaPinFunction == null) {
            try {
                throw new I2CMasterConfigurationException(ExceptionMessage.PIN_FIELD_IS_NOT_VALID_MESSAGE, "SDAPinFunction");
            } catch (I2CMasterConfigurationException i2CMasterConfigurationException) {
                throw new RuntimeException(i2CMasterConfigurationException.getMessage());
            }
        }

        if (sclPin == null) {
            try {
                throw new I2CMasterConfigurationException(ExceptionMessage.PIN_FIELD_IS_NOT_VALID_MESSAGE, "SCLPinNumber");
            } catch (I2CMasterConfigurationException i2CMasterConfigurationException) {
                throw new RuntimeException(i2CMasterConfigurationException.getMessage());
            }
        }

        if (sclPinFunction == null) {
            try {
                throw new I2CMasterConfigurationException(ExceptionMessage.PIN_FIELD_IS_NOT_VALID_MESSAGE, "SCLPinFunction");
            } catch (I2CMasterConfigurationException i2CMasterConfigurationException) {
                throw new RuntimeException(i2CMasterConfigurationException.getMessage());
            }
        }

        if (busClockInHertz < 100000) {
            try {
                throw new I2CMasterConfigurationException(ExceptionMessage.PIN_FIELD_IS_NOT_VALID_MESSAGE, "busClockHertz<100000");
            } catch (I2CMasterConfigurationException i2CMasterConfigurationException) {
                throw new RuntimeException(i2CMasterConfigurationException.getMessage());
            }
        }
        if (busClockStretchTimout < 0) { // ??
            try {
                throw new I2CMasterConfigurationException(ExceptionMessage.PIN_FIELD_IS_NOT_VALID_MESSAGE, "busClockStretchTimout<0");
            } catch (I2CMasterConfigurationException i2CMasterConfigurationException) {
                throw new RuntimeException(i2CMasterConfigurationException.getMessage());
            }
        }

        this.i2CBus = i2CBus;
        this.sdaPin = sdaPin;
        this.sdaPinFunction = sdaPinFunction;
        this.sclPin = sclPin;
        this.sclPinFunction = sclPinFunction;
        this.busClockInHertz = busClockInHertz;
        this.busClockStretchTimout = busClockStretchTimout;
    }

    static class I2CMasterBusNumberConfiguratorImpl implements I2CMasterBusNumberConfigurator {

        @Override
        public I2CMasterPropertyConfigurator bus(I2CBus i2CBus) {
            return new I2CMasterPropertyConfiguratorImpl(i2CBus);
        }
    }

    private static class I2CMasterPropertyConfiguratorImpl implements I2CMasterPropertyConfigurator {

        private final I2CBus i2CBus;
        private Pin sdaPin;
        private PinFunction sdaPinFunction;
        private Pin sclPin;
        private PinFunction sclPinFunction;
        private int busClockInHertz;
        private int busClockStretchTimout;


        private I2CMasterPropertyConfiguratorImpl(I2CBus i2CBus) {
            this.i2CBus = i2CBus;
        }

        @Override
        public I2CMasterPropertyConfigurator sdaPin(Pin sdaPin, PinFunction sdaPinFunction) {
            this.sdaPin = sdaPin;
            this.sdaPinFunction = sdaPinFunction;
            return this;
        }

        @Override
        public I2CMasterPropertyConfigurator sclPin(Pin sclPin, PinFunction sclPinFunction) {
            this.sclPin = sclPin;
            this.sclPinFunction = sclPinFunction;
            return this;
        }

        @Override
        public I2CMasterPropertyConfigurator busClockInHertz(int busClockInHertz) {
            this.busClockInHertz = busClockInHertz;
            return this;
        }

        @Override
        public I2CMasterPropertyConfigurator busClockStretchTimeout(int busClockStretchTimeout) {
            this.busClockStretchTimout = busClockStretchTimeout;
            return this;
        }

        @Override
        public I2CMasterConfigurator build() {
            return new I2CMasterConfiguratorImpl(
                    i2CBus,
                    sdaPin,
                    sdaPinFunction,
                    sclPin,
                    sclPinFunction,
                    busClockInHertz,
                    busClockStretchTimout);
        }
    }

    @Override
    public I2CBus getBus() {
        return i2CBus;
    }

    @Override
    public Pin getSDAPin() {
        return sdaPin;
    }

    @Override
    public PinFunction getSDAPinFunction() {
        return sdaPinFunction;
    }

    @Override
    public Pin getSCLPin() {
        return sclPin;
    }

    @Override
    public PinFunction getSCLPinFunction() {
        return sclPinFunction;
    }

    @Override
    public int getBusClockInHertz() {
        return busClockInHertz;
    }

    @Override
    public int getBusClockStretchTimeout() {
        return busClockStretchTimout;
    }

    @Override
    public String toString() {
        return new StringJoiner(", ", I2CMasterConfiguratorImpl.class.getSimpleName() + "[", "]")
                .add("i2CBus=" + i2CBus)
                .add("sdaPin=" + sdaPin)
                .add("sdaPinFunction=" + sdaPinFunction)
                .add("sclPin=" + sclPin)
                .add("sclPinFunction=" + sclPinFunction)
                .add("busClockInHertz=" + busClockInHertz)
                .add("busClockStretchTimout=" + busClockStretchTimout)
                .toString();
    }
}


