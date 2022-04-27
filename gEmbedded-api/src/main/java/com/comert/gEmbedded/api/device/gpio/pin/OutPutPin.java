package com.comert.gEmbedded.api.device.gpio.pin;

public interface OutPutPin {

    OutPutPin getInstanceIfExist(Pin pin);

    Pin getPin();

    void write();

    void clear();

    boolean isLow();

    boolean isHigh();

}
