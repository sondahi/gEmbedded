package com.comert.gEmbedded.api.device.gpio.pin;

public interface PWMPin {

    PWMPin getInstanceIfExist(Pin pin);

    Pin getPin();

    PWMType getPWMType();

    void pulse(int periodInMicSec, int dutyCycleInMicSec);

}
