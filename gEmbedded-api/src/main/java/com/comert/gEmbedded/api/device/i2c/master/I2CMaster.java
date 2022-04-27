package com.comert.gEmbedded.api.device.i2c.master;

import com.comert.gEmbedded.api.device.common.exception.IOException;
import com.comert.gEmbedded.api.device.gpio.pin.Pin;
import com.comert.gEmbedded.api.device.gpio.pin.PinFunction;

/**
 * This is a test javadoc.
 * How are you by the way?.
 * <p>
 * This method always returns immediately, whether or not the
 * image exists. When this applet attempts to draw the image on
 * the screen, the data will be loaded. The graphics primitives
 * that draw the image will incrementally paint on the screen.
 * @author gökay cömert
 */
public interface I2CMaster {

    I2CMaster getInstance(I2CBus i2CBus);

    I2CBus getBus();

    Pin getSDAPin();

    PinFunction getSDAPinFunction();

    Pin getSCLPin();

    PinFunction getSCLPinFunction();

    int getBusClockInHertz();

    int getBusClockStretchTimeout();

    void sendData(byte slaveAddress, byte[] dataToSend) throws IOException;

    void sendData(byte slaveAddress, byte[] dataToSend, int dataToSendSize) throws IOException;

    void receiveData(byte slaveAddress, int[] dataToReceive) throws IOException;

    void receiveData(byte slaveAddress, int[] dataToReceive, int dataToReceiveSize) throws IOException;

    void sendAndReceiveData(byte slaveAddress, byte[] dataToSend, int[] dataToReceive) throws IOException;

    void sendAndReceiveData(byte slaveAddress, byte[] dataToSend, int dataToSendSize, int[] dataToReceive, int dataToReceiveSize) throws IOException;

    void writeRegister(byte slaveAddress, byte registerAddress, byte dataToSend) throws IOException;

    /**
     * This is a test javadoc.
     * How are you by the way?.
     * @param slaveAddress addres of i2c Slave
     * @param registerAddress register adress of i2c Slave
     * @return integer value of register
     */
    int readRegister(byte slaveAddress, byte registerAddress) throws IOException;

    int writeAndReadRegister(byte slaveAddress, byte registerAddress, byte dataToSend) throws IOException;

    void write(byte slaveAddress, byte dataToSend) throws IOException;

    int read(byte slaveAddress) throws IOException;

}
