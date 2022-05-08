package com.comert.gEmbedded.api.device.exception;

public class DeviceExecutionException extends DeviceException {

    public DeviceExecutionException(ExceptionMessage exceptionMessage, String property) {
        super(exceptionMessage, property);
    }

}
