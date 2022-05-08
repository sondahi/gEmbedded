package com.comert.gEmbedded.pi.device.configurator;

import com.comert.gEmbedded.api.device.exception.ExceptionMessage;
import com.comert.gEmbedded.api.device.exception.I2CMasterConfigurationException;
import com.comert.gEmbedded.api.device.exception.JNIException;
import com.comert.gEmbedded.api.device.exception.PinConfigurationException;
import com.comert.gEmbedded.api.device.gpio.pin.Pin;
import com.comert.gEmbedded.api.device.gpio.pin.PullUpDownStatus;
import com.comert.gEmbedded.api.device.gpio.pin.configurator.InPutPinConfigurator;
import com.comert.gEmbedded.api.device.gpio.pin.configurator.OutPutPinConfigurator;
import com.comert.gEmbedded.api.device.gpio.pin.configurator.PWMPinConfigurator;
import com.comert.gEmbedded.api.device.i2c.master.I2CBus;
import com.comert.gEmbedded.api.device.i2c.master.configurator.I2CMasterConfigurator;
import com.comert.gEmbedded.nativeinterface.GPIOController;
import com.comert.gEmbedded.nativeinterface.I2CMasterController;

import java.util.HashSet;
import java.util.Set;

public final class ConfigurationVisitor {

    private static final ConfigurationVisitor INSTANCE;
    private static final String GPIO_EVENT_FILE = "/dev/gpiochip0";
    private static final String DIGIT_METHOD_NAME = "getDigit";
    private static final String DIGIT_METHOD_SIGNATURE = "()I";
    private static final String TEXT_METHOD_NAME = "getText";
    private static final String TEXT_METHOD_SIGNATURE = "()Ljava/lang/String;";

    static {
        INSTANCE = new ConfigurationVisitor();
    }

    private final Set<Pin> notSupportedPins = new HashSet<>();
    private final Set<Pin> configuredPins = new HashSet<>();
    private final Set<I2CBus> notSupportedI2CBusses = new HashSet<>();
    private final Set<I2CBus> configuredI2CBusses = new HashSet<>();

    {
        notSupportedPins.add(Pin.PIN_30); // change
        notSupportedI2CBusses.add(I2CBus.BUS_2); // add
    }

    private ConfigurationVisitor() {

    }

    public static ConfigurationVisitor getInstance() {
        return INSTANCE;
    }

    public synchronized void accept(InPutPinConfigurator inPutPinConfigurator) throws PinConfigurationException, JNIException {
        checkIfPinIsNotSupportedAndIsAlreadyRegistered(inPutPinConfigurator.getPin());

        if (inPutPinConfigurator.isEventConfigured()) {
            GPIOController.setEventDetectStatus(inPutPinConfigurator.getPin(), inPutPinConfigurator.getEventDetectStatus(), DIGIT_METHOD_NAME, DIGIT_METHOD_SIGNATURE, GPIO_EVENT_FILE);
        } else {
            GPIOController.setPinFunction(inPutPinConfigurator.getPin(), inPutPinConfigurator.getPinFunction(), DIGIT_METHOD_NAME, DIGIT_METHOD_SIGNATURE);
        }

        if (inPutPinConfigurator.getPullUpDownStatus() != PullUpDownStatus.NONE) {
            GPIOController.setPullUpDownStatus(inPutPinConfigurator.getPin(), inPutPinConfigurator.getPullUpDownStatus(), DIGIT_METHOD_NAME, DIGIT_METHOD_SIGNATURE);
        }
    }

    public synchronized void accept(OutPutPinConfigurator outPutPinConfigurator) throws PinConfigurationException, JNIException {
        checkIfPinIsNotSupportedAndIsAlreadyRegistered(outPutPinConfigurator.getPin());

        GPIOController.setPinFunction(outPutPinConfigurator.getPin(), outPutPinConfigurator.getPinFunction(), DIGIT_METHOD_NAME, DIGIT_METHOD_SIGNATURE);
    }

    public synchronized void accept(PWMPinConfigurator pwmPinConfigurator) throws PinConfigurationException, JNIException {
        checkIfPinIsNotSupportedAndIsAlreadyRegistered(pwmPinConfigurator.getPin());

        GPIOController.setPinFunction(pwmPinConfigurator.getPin(), pwmPinConfigurator.getPinFunction(), DIGIT_METHOD_NAME, DIGIT_METHOD_SIGNATURE);
    }

    public synchronized void accept(I2CMasterConfigurator i2CMasterConfigurator) throws PinConfigurationException, JNIException, I2CMasterConfigurationException {
        checkIfPinIsNotSupportedAndIsAlreadyRegistered(i2CMasterConfigurator.getSDAPin());
        checkIfPinIsNotSupportedAndIsAlreadyRegistered(i2CMasterConfigurator.getSCLPin());
        checkIfBusIsNotSupportedAndIsAlreadyRegistered(i2CMasterConfigurator.getBus());

        GPIOController.setPinFunction(i2CMasterConfigurator.getSDAPin(), i2CMasterConfigurator.getSDAPinFunction(), DIGIT_METHOD_NAME, DIGIT_METHOD_SIGNATURE);
        GPIOController.setPinFunction(i2CMasterConfigurator.getSCLPin(), i2CMasterConfigurator.getSCLPinFunction(), DIGIT_METHOD_NAME, DIGIT_METHOD_SIGNATURE);
        I2CMasterController.setMaster(i2CMasterConfigurator.getBus(), DIGIT_METHOD_NAME, DIGIT_METHOD_SIGNATURE, i2CMasterConfigurator.getBusClockInHertz(), i2CMasterConfigurator.getBusClockStretchTimeout());

    }

    private void checkIfPinIsNotSupportedAndIsAlreadyRegistered(final Pin pin) throws PinConfigurationException {
        if (notSupportedPins.contains(pin)) {
            throw new PinConfigurationException(ExceptionMessage.PIN_TYPE_IS_NOT_SUPPORTED_MESSAGE, pin.getText());
        }
        if (configuredPins.contains(pin)) {
            throw new PinConfigurationException(ExceptionMessage.PIN_IS_ALREADY_CONFIGURED_MESSAGE, pin.getText());
        } else {
            configuredPins.add(pin);
        }
    }

    private void checkIfBusIsNotSupportedAndIsAlreadyRegistered(final I2CBus i2CBus) throws I2CMasterConfigurationException {
        if (notSupportedI2CBusses.contains(i2CBus)) {
            throw new I2CMasterConfigurationException(ExceptionMessage.I2C_BUS_NUMBER_IS_NOT_SUPPORTED_MESSAGE, i2CBus.getText());
        }
        if (configuredI2CBusses.contains(i2CBus)) {
            throw new I2CMasterConfigurationException(ExceptionMessage.I2C_BUS_IS_ALREADY_CONFIGURED_MESSAGE, i2CBus.getText());
        } else {
            configuredI2CBusses.add(i2CBus);
        }
    }

}
