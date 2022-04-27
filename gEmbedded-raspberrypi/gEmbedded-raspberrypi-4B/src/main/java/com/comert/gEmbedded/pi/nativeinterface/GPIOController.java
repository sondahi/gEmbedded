package com.comert.gEmbedded.pi.nativeinterface;

import com.comert.gEmbedded.api.device.common.exception.JNIException;
import com.comert.gEmbedded.api.device.gpio.pin.EventDetectStatus;
import com.comert.gEmbedded.api.device.gpio.pin.Pin;
import com.comert.gEmbedded.api.device.gpio.pin.PinFunction;
import com.comert.gEmbedded.api.device.gpio.pin.PullUpDownStatus;

public abstract class GPIOController {

    private GPIOController() {
    }

    public static native void setPinFunction(Pin pin, PinFunction pinFunction, String enumMethodName, String enumMethodSignature) throws JNIException;

    public static native void setPullUpDownStatus(Pin pin, PullUpDownStatus pullUpDownStatus, String enumMethodName, String enumMethodSignature) throws JNIException;

    public static native void setEventDetectStatus(Pin pin, EventDetectStatus eventDetectStatus, String enumMethodName, String enumMethodSignature, String fileName) throws JNIException;

    public static native boolean isHigh(final int registerSelector, final int pinSet);

    public static native boolean isLow(final int registerSelector, final int pinSet);

    public static native void write(final int registerSelector, final int pinSet);

    public static native void clear(final int registerSelector, final int pinSet);

    public static native void pulse(final int registerSelector, final int pinSet, final int highSleepTime, final int lowSleepTime);

    public static native int poll(final int pinNumber, final int timeoutInMilSec);

    public static native void releaseGPIOThreadRecourse(final int pinNumber);

}
