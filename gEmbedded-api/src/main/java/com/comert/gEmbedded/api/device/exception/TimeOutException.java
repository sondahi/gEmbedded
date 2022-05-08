package com.comert.gEmbedded.api.device.exception;

public class TimeOutException extends DeviceException {

    public TimeOutException(ExceptionMessage exceptionMessage, String property) {
        super(exceptionMessage, property);
    }

}
