package com.comert.gEmbedded.api.device.exception;

public abstract class DeviceException extends Exception {

    private final String property;

    protected DeviceException(ExceptionMessage exceptionMessage, String property) {
        super(exceptionMessage.toString());
        this.property = property;
    }

    @Override
    public String getMessage() {
        return super.getMessage() + " : " + property;
    }
}
