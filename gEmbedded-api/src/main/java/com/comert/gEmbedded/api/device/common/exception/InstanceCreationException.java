package com.comert.gEmbedded.api.device.common.exception;

public final class InstanceCreationException extends DeviceException {

    public InstanceCreationException(ExceptionMessage exceptionMessage, String property) {
        super(exceptionMessage, property);
    }
}
