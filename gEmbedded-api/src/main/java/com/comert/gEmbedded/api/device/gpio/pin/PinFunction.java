package com.comert.gEmbedded.api.device.gpio.pin;

import com.comert.gEmbedded.api.device.DeviceConstant;

public enum PinFunction implements DeviceConstant {

    INPUT(0b000, "Input"),
    OUTPUT(0b001, "Output"),
    ALT0(0b100, "Alternate 0"),
    ALT1(0b101, "Alternate 1"),
    ALT2(0b110, "Alternate 2"),
    ALT3(0b111, "Alternate 3"),
    ALT4(0b011, "Alternate 4"),
    ALT5(0b010, "Alternate 5");

    PinFunction(int digit, String text) {
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
