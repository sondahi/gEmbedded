package com.comert.gEmbedded.nativeinterface;

import com.comert.gEmbedded.api.device.gpio.pin.EventDetectStatus;
import com.comert.gEmbedded.api.device.gpio.pin.Pin;
import com.comert.gEmbedded.api.device.gpio.pin.PinFunction;
import com.comert.gEmbedded.api.device.gpio.pin.PullUpDownStatus;

public abstract class GPIOController {

    private GPIOController() {
    }

    public static native int calculate1bitRegisterSelector (Pin pin);

    public static native int calculate1bitPinSet (Pin pin);

    public static native void setPinFunction(Pin pin, PinFunction pinFunction);

    public static native PinFunction readPinFunction(Pin pin);

    public static native void setPullUpDownStatus(Pin pin, PullUpDownStatus pullUpDownStatus);

    public static native PullUpDownStatus readPullUpDownStatus(Pin pin);

    public static native void setEventDetectStatus(Pin pin, EventDetectStatus eventDetectStatus);

    public static native EventDetectStatus readEventDetectStatus(Pin pin);

    public static native boolean isPinHigh(int registerSelector, int pinSet);

    public static native boolean isPinLow(int registerSelector, int pinSet);

    public static native void writePin(int registerSelector, int pinSet);

    public static native void writePinFaster(int registerSelector, int pinSet);

    public static native void clearPin(int registerSelector, int pinSet);

    public static native void clearPinFaster(int registerSelector, int pinSet);

    public static native void pulsePin(int registerSelector, int pinSet, int highSleepTime, int lowSleepTime);

    public static native void pulsePinFaster(int registerSelector, int pinSet, int highSleepTimeInMicSec, int lowSleepTimeInMicSec);

    public static native int pollEvent(int pinNumber, int timeoutInMilSec);

    public static native void releaseGPIOThreadRecourse(int pinNumber);

}
