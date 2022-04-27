package com.comert.gEmbedded.api.device.common.exception;

public class DeviceExecutionException extends DeviceException {

    public DeviceExecutionException(ExceptionMessage exceptionMessage, String property) {
        super(exceptionMessage, property);
    }

}
