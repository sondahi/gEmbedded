package com.comert.gEmbedded.api.device.common.exception;

public class IOException extends DeviceException{

    public IOException(ExceptionMessage exceptionMessage, String property) {
        super(exceptionMessage, property);
    }

}
