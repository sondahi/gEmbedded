package com.comert.gEmbedded.api.device.gpio.pin;

import com.comert.gEmbedded.api.device.DeviceConstant;

public enum PinFunction implements DeviceConstant {

    ALT0(0, "Alternate 0"),
    ALT1(1, "Alternate 1"),
    ALT2(2, "Alternate 2"),
    ALT3(3, "Alternate 3"),
    ALT4(4, "Alternate 4"),
    ALT5(5, "Alternate 5"),
    INPUT(6, "Input"),
    OUTPUT(7, "Output");


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
