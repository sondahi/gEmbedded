package com.comert.gEmbedded.api.device.common.exception;

public enum ExceptionMessage {

    PROVIDER_COULD_NOT_BE_FOUND_IN_IMPL_PACKAGE_MESSAGE("Provider could not be found in the implementation package"),
    PROVIDER_DOES_NOT_IMPLEMENT_PARENT_CLASS_MESSAGE("Provider does not implement parent class"),
    PROVIDER_DOES_NOT_HAVE_A_DEFAULT_CONSTRUCTOR_MESSAGE("Provider does not have a default constructor"),
    PROVIDER_COULD_NOT_BE_CONSTRUCTED_MESSAGE("Provider could not be constructed"),
    PROVIDER_DOES_NOT_IMPLEMENT_INTERFACE_METHOD_MESSAGE("Provider does not implement interface method"),

    INSTANCE_CREATED_OUT_OF_DESIRED_CLASS_MESSAGE("Instance was created out of desired class"),
    INSTANCE_IS_NOT_CREATED_MESSAGE("Instance is not created. Before getting instance you must create it in the Factory"),


    DEVICE_IS_ALREADY_SET_UP_MESSAGE("Device is already set up"),
    DEVICE_IS_ALREADY_SHUT_DOWN_MESSAGE("Device is already shut down"),
    DEVICE_MUST_BE_SETUP_MESSAGE("Device must be set up"),

    PIN_TYPE_IS_NOT_SUPPORTED_MESSAGE("Pin type is not supported"),
    PIN_IS_ALREADY_CONFIGURED_MESSAGE("Pin is already configured"),
    PIN_NUMBER_IS_NOT_SUPPORTED_MESSAGE("Pin number is not supported by provider or device"),
    PIN_FIELD_IS_NOT_VALID_MESSAGE("Pin Field is not valid"),

    I2C_BUS_IS_ALREADY_CONFIGURED_MESSAGE("I2C bus is already configured"),
    I2C_BUS_NUMBER_IS_NOT_SUPPORTED_MESSAGE("I2C bus number is not supported by provider or device"),

    TIME_OUT_EXCEPTION_MESSAGE("Time out occurred"),

    IO_EXCEPTION_MESSAGE("Error occurred while IO operation"),

    JNI_EXCEPTION_MESSAGE("Error occurred in native library");

    ExceptionMessage(String message) {
        this.message = message;
    }

    private final String message;

    @Override
    public String toString() {
        return message;
    }

}