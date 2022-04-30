package com.comert.gEmbedded.api.device.gpio.pin;

import com.comert.gEmbedded.api.device.DeviceConstant;

public enum PinType implements DeviceConstant {

    DIGITAL(0, "Digital"),
    ANALOG(1, "Analog"),
    ALTERNATE(2,"Alternate");


    PinType(int digit, String text) {
        this.digit = digit;
        this.text = text;
    }

    private final int digit;

    private final String text;

    @Override
    public int getDigit() {
        return digit;
    }

    @Override
    public String getText() {
        return text;
    }

}
