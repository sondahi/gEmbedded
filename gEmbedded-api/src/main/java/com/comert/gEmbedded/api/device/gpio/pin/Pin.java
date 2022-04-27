package com.comert.gEmbedded.api.device.gpio.pin;

import com.comert.gEmbedded.api.device.DeviceConstant;

public enum Pin implements DeviceConstant {

    PIN_0(0, "Zero"),
    PIN_1(1, "One"),
    PIN_2(2, "Two"),
    PIN_3(3, "Three"),
    PIN_4(4, "Four"),
    PIN_5(5, "Five"),
    PIN_6(6, "Six"),
    PIN_7(7, "Seven"),
    PIN_8(8, "Eight"),
    PIN_9(9, "Nine"),
    PIN_10(10, "Ten"),
    PIN_11(11, "Eleven"),
    PIN_12(12, "Twelve"),
    PIN_13(13, "Thirteen"),
    PIN_14(14, "Fourteen"),
    PIN_15(15, "Fifteen"),
    PIN_16(16, "Sixteen"),
    PIN_17(17, "Seventeen"),
    PIN_18(18, "Eighteen"),
    PIN_19(19, "Nineteen"),
    PIN_20(20, "Twenty"),
    PIN_21(21, "Twenty one"),
    PIN_22(22, "Twenty two"),
    PIN_23(23, "Twenty three"),
    PIN_24(24, "Twenty four"),
    PIN_25(25, "Twenty five"),
    PIN_26(26, "Twenty six"),
    PIN_27(27, "Twenty seven"),
    PIN_28(28, "Twenty eight"),
    PIN_29(29, "Twenty nine"),
    PIN_30(30, "Thirty");

    Pin(int digit, String text) {
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
