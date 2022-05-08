package com.comert.gEmbedded.api.device.exception;

public final class InstanceCreationException extends DeviceException {

    public InstanceCreationException(ExceptionMessage exceptionMessage, String property) {
        super(exceptionMessage, property);
    }
}
