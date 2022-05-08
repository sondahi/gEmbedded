package com.comert.gEmbedded.api.device.exception;

public final class PinConfigurationException extends DeviceException {

    public PinConfigurationException(ExceptionMessage exceptionMessage, String property) {
        super(exceptionMessage, property);
    }
}
