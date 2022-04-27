package com.comert.gEmbedded.api.device.common.exception;

public class InstanceIsNotCreatedException extends DeviceException{

    public InstanceIsNotCreatedException(ExceptionMessage exceptionMessage, String property) {
        super(exceptionMessage, property);
    }
}
