package com.comert.gEmbedded.api.device.common.exception;

public class JNIException extends DeviceException {

    public JNIException(String property) {
        this(ExceptionMessage.JNI_EXCEPTION_MESSAGE, property);
    }

    public JNIException(ExceptionMessage exceptionMessage, String property) {
        super(exceptionMessage, property);
    }
}
