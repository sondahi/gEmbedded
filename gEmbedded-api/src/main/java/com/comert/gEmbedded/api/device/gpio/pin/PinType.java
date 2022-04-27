package com.comert.gEmbedded.api.device.gpio.pin;

import com.comert.gEmbedded.api.device.DeviceConstant;

public enum PinType implements DeviceConstant {

    ALTERNATE(0,"Alternate"),
    DIGITAL(1, "Digital"),
    ANALOG(2, "Analog");

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
