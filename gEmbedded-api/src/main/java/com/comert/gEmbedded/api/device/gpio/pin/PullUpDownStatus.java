package com.comert.gEmbedded.api.device.gpio.pin;

import com.comert.gEmbedded.api.device.DeviceConstant;

public enum PullUpDownStatus implements DeviceConstant {

    NONE(0b00, "None"),
    PULL_UP(0b01, "Pull up"),
    PULL_DOWN(0b10, "Pull Down"),
    RESERVED(0b11, "Reserved"),
    DEFAULT(0, "Default");

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
