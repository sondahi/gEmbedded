package com.comert.gEmbedded.nativeinterface;

import com.comert.gEmbedded.api.device.exception.JNIException;
import com.comert.gEmbedded.api.device.gpio.pin.EventDetectStatus;
import com.comert.gEmbedded.api.device.gpio.pin.Pin;
import com.comert.gEmbedded.api.device.gpio.pin.PinFunction;
import com.comert.gEmbedded.api.device.gpio.pin.PullUpDownStatus;

public abstract class GPIOController {

    private GPIOController() {
    }

    public static native void setPinFunction(Pin pin, PinFunction pinFunction) throws JNIException;

    public static native void setPullUpDownStatus(Pin pin, PullUpDownStatus pullUpDownStatus) throws JNIException;

    public static native void setEventDetectStatus(Pin pin, EventDetectStatus eventDetectStatus) throws JNIException;

    public static native int getRegisterSelector(Pin pin);

    public static native int getPinSet(Pin pin);

    public static native boolean isHigh(int registerSelector, int pinSet);

    public static native boolean isLow(int registerSelector, int pinSet);

    public static native void write(int registerSelector, int pinSet);

    public static native void clear(int registerSelector, int pinSet);

    public static native void pulse(int registerSelector, int pinSet, int highSleepTime, int lowSleepTime);

    public static native int poll(int pinNumber, int timeoutInMilSec);

    public static native void releaseGPIOThreadRecourse(int pinNumber);

}
