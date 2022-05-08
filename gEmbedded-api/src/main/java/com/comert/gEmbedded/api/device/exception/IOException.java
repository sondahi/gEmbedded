package com.comert.gEmbedded.api.device.exception;

public class IOException extends DeviceException{

    public IOException(ExceptionMessage exceptionMessage, String property) {
        super(exceptionMessage, property);
    }

}
