package com.comert.gEmbedded.api.device.gpio.pin;

import com.comert.gEmbedded.api.device.DeviceConstant;

public enum PullUpDownStatus implements DeviceConstant {

    NONE(0, "None"),
    PULL_UP(1, "Pull up"),
    PULL_DOWN(2, "Pull Down"),
    DEFAULT(3, "Default"),
    RESERVED(4, "Reserved");

    PullUpDownStatus(int digit, String text) {
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
