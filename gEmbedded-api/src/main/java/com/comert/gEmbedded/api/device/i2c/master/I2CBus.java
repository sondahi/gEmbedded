package com.comert.gEmbedded.api.device.i2c.master;

import com.comert.gEmbedded.api.device.DeviceConstant;

public enum I2CBus implements DeviceConstant {

    BUS_0(0, "Bus 0"),
    BUS_1(1, "Bus 1"),
    BUS_2(2, "Bus 2");


    I2CBus(int digit, String text) {
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
