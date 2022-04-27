package com.comert.gEmbedded.pi.device.i2c.master;

import com.comert.gEmbedded.api.device.common.exception.ExceptionMessage;
import com.comert.gEmbedded.api.device.common.exception.IOException;
import com.comert.gEmbedded.api.device.common.exception.InstanceIsNotCreatedException;
import com.comert.gEmbedded.api.device.common.exception.JNIException;
import com.comert.gEmbedded.api.device.gpio.pin.Pin;
import com.comert.gEmbedded.api.device.gpio.pin.PinFunction;
import com.comert.gEmbedded.api.device.i2c.impl.I2CMasterImpl;
import com.comert.gEmbedded.api.device.i2c.master.I2CBus;
import com.comert.gEmbedded.api.device.i2c.master.I2CMaster;
import com.comert.gEmbedded.api.device.i2c.master.configurator.I2CMasterConfigurator;
import com.comert.gEmbedded.pi.nativeinterface.I2CMasterController;

import java.util.HashMap;
import java.util.Map;

public class I2CMasterParent extends I2CMasterImpl {

    private static final Map<I2CBus, I2CMaster> createdI2CMasters = new HashMap<>();

    protected final I2CBus i2CBus;
    protected final Pin sdaPin;
    protected final PinFunction sdaPinFunction;
    protected final Pin sclPin;
    protected final PinFunction sclPinFunction;
    protected final int busClockInHertz;
    protected final int busClockStretchTimeout;

    private final int busSelector;

    public I2CMasterParent(I2CMasterConfigurator i2CMasterConfigurator) {
        i2CBus = i2CMasterConfigurator.getBus();
        sdaPin = i2CMasterConfigurator.getSDAPin();
        sdaPinFunction = i2CMasterConfigurator.getSDAPinFunction();
        sclPin = i2CMasterConfigurator.getSCLPin();
        sclPinFunction = i2CMasterConfigurator.getSCLPinFunction();
        this.busClockInHertz = i2CMasterConfigurator.getBusClockInHertz();
        this.busClockStretchTimeout = i2CMasterConfigurator.getBusClockStretchTimeout();
        this.busSelector = i2CBus.getDigit();

        createdI2CMasters.put(i2CBus, this);
    }

    @Override
    public I2CMaster getInstance(I2CBus i2CBus) {
        if (createdI2CMasters.containsKey(i2CBus)) {
            return createdI2CMasters.get(i2CBus);
        } else {
            try {
                throw new InstanceIsNotCreatedException(ExceptionMessage.INSTANCE_IS_NOT_CREATED_MESSAGE, i2CBus.getText());
            } catch (InstanceIsNotCreatedException InstanceIsNotCreatedException) {
                throw new RuntimeException(InstanceIsNotCreatedException.getMessage());
            }
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
        return busClockStretchTimeout;
    }

    @Override
    public final synchronized void sendData(byte slaveAddress, byte[] dataToSend) throws IOException {
        try {
            I2CMasterController.sendData(busSelector, slaveAddress, dataToSend, dataToSend.length);
        } catch (JNIException jniException) {
            throw new IOException(ExceptionMessage.IO_EXCEPTION_MESSAGE, jniException.getMessage());
        }
    }

    @Override
    public final synchronized void sendData(byte slaveAddress, byte[] dataToSend, int dataToSendSize) throws IOException {
        try {
            I2CMasterController.sendData(busSelector, slaveAddress, dataToSend, dataToSendSize);
        } catch (JNIException jniException) {
            throw new IOException(ExceptionMessage.IO_EXCEPTION_MESSAGE, jniException.getMessage());
        }
    }

    @Override
    public final synchronized void receiveData(byte slaveAddress, int[] dataToReceive) throws IOException {
        try {
            I2CMasterController.receiveData(busSelector, slaveAddress, dataToReceive, dataToReceive.length);
        } catch (JNIException jniException) {
            throw new IOException(ExceptionMessage.IO_EXCEPTION_MESSAGE, jniException.getMessage());
        }
    }

    @Override
    public final synchronized void receiveData(byte slaveAddress, int[] dataToReceive, int dataToReceiveSize) throws IOException {
        try {
            I2CMasterController.receiveData(busSelector, slaveAddress, dataToReceive, dataToReceiveSize);
        } catch (JNIException jniException) {
            throw new IOException(ExceptionMessage.IO_EXCEPTION_MESSAGE, jniException.getMessage());
        }
    }

    @Override
    public final synchronized void sendAndReceiveData(byte slaveAddress, byte[] dataToSend, int[] dataToReceive) throws IOException {
        try {
            I2CMasterController.sendAndReceiveData(busSelector, slaveAddress, dataToSend, dataToSend.length, dataToReceive, dataToReceive.length);
        } catch (JNIException jniException) {
            throw new IOException(ExceptionMessage.IO_EXCEPTION_MESSAGE, jniException.getMessage());
        }
    }

    @Override
    public final synchronized void sendAndReceiveData(byte slaveAddress, byte[] dataToSend, int dataToSendSize, int[] dataToReceive, int dataToReceiveSize) throws IOException {
        try {
            I2CMasterController.sendAndReceiveData(busSelector, slaveAddress, dataToSend, dataToSendSize, dataToReceive, dataToReceiveSize);
        } catch (JNIException jniException) {
            throw new IOException(ExceptionMessage.IO_EXCEPTION_MESSAGE, jniException.getMessage());
        }
    }


    @Override
    public final synchronized void writeRegister(byte slaveAddress, byte registerAddress, byte dataToSend) throws IOException {
        try {
            I2CMasterController.writeRegister(busSelector, slaveAddress, registerAddress, dataToSend);
        } catch (JNIException jniException) {
            throw new IOException(ExceptionMessage.IO_EXCEPTION_MESSAGE, jniException.getMessage());
        }
    }

    @Override
    public final synchronized int readRegister(byte slaveAddress, byte registerAddress) throws IOException {
        try {
            return I2CMasterController.readRegister(busSelector, slaveAddress, registerAddress);
        } catch (JNIException jniException) {
            throw new IOException(ExceptionMessage.IO_EXCEPTION_MESSAGE, jniException.getMessage());
        }
    }


    @Override
    public final synchronized int writeAndReadRegister(byte slaveAddress, byte registerAddress, byte dataToSend) throws IOException {
        try {
            return I2CMasterController.writeAndReadRegister(busSelector, slaveAddress, registerAddress, dataToSend);
        } catch (JNIException jniException) {
            throw new IOException(ExceptionMessage.IO_EXCEPTION_MESSAGE, jniException.getMessage());
        }
    }

    @Override
    public final synchronized void write(byte slaveAddress, byte dataToSend) throws IOException {
        try {
            I2CMasterController.write(busSelector, slaveAddress, dataToSend);
        } catch (JNIException jniException) {
            throw new IOException(ExceptionMessage.IO_EXCEPTION_MESSAGE, jniException.getMessage());
        }
    }

    @Override
    public final synchronized int read(byte slaveAddress) throws IOException {
        try {
            return I2CMasterController.read(busSelector, slaveAddress);
        } catch (JNIException jniException) {
            throw new IOException(ExceptionMessage.IO_EXCEPTION_MESSAGE, jniException.getMessage());
        }
    }


}
