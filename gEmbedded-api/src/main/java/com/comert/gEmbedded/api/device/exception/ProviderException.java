package com.comert.gEmbedded.api.device.exception;

public final class ProviderException extends DeviceException {

    public ProviderException(ExceptionMessage exceptionMessage, String property) {
        super(exceptionMessage, property);
    }
}
