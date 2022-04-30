package com.comert.gEmbedded.api.device.gpio.pin;

import com.comert.gEmbedded.api.device.DeviceConstant;

public enum EventDetectStatus implements DeviceConstant {

    FALLING(0, "Falling"),
    RISING(1, "Rising"),
    BOTH(2, "Both");

    EventDetectStatus(int digit, String text) {
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
