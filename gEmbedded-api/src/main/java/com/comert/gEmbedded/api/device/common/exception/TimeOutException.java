package com.comert.gEmbedded.api.device.common.exception;

public class TimeOutException extends DeviceException {

    public TimeOutException(ExceptionMessage exceptionMessage, String property) {
        super(exceptionMessage, property);
    }

}
