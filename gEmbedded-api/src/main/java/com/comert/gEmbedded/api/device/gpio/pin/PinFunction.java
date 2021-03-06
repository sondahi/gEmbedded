package com.comert.gEmbedded.api.device.gpio.pin;

import com.comert.gEmbedded.api.device.DeviceConstant;

public enum PinFunction implements DeviceConstant {

    ALT_0(0, "Alternate 0"),
    ALT_1(1, "Alternate 1"),
    ALT_2(2, "Alternate 2"),
    ALT_3(3, "Alternate 3"),
    ALT_4(4, "Alternate 4"),
    ALT_5(5, "Alternate 5"),
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
