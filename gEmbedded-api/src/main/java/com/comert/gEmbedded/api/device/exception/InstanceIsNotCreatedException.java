package com.comert.gEmbedded.api.device.exception;

public class InstanceIsNotCreatedException extends DeviceException{

    public InstanceIsNotCreatedException(ExceptionMessage exceptionMessage, String property) {
        super(exceptionMessage, property);
    }
}
