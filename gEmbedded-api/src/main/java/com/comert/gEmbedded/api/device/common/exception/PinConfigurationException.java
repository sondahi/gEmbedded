package com.comert.gEmbedded.api.device.common.exception;

public final class PinConfigurationException extends DeviceException {

    public PinConfigurationException(ExceptionMessage exceptionMessage, String property) {
        super(exceptionMessage, property);
    }
}
