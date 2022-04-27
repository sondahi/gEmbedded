package com.comert.gEmbedded.api.device.common.exception;

public class I2CMasterConfigurationException extends DeviceException {

    public I2CMasterConfigurationException(ExceptionMessage exceptionMessage, String property) {
        super(exceptionMessage, property);
    }
}
