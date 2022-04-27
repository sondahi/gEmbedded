package com.comert.gEmbedded.api.device.gpio.pin;

import com.comert.gEmbedded.api.device.gpio.listener.GPIOEventListener;

import java.util.Optional;

public interface InPutPin {

    InPutPin getInstanceIfExist(Pin pin);

    Pin getPin();

    PinType getPinType();

    PullUpDownStatus getPullUpDownStatus();

    EventDetectStatus getEventDetectStatus();

    int getEventTimeout();

    Optional<GPIOEventListener> getEventListener();

    boolean isLow();

    boolean isHigh();

    double read();

    void startListener();

    void suspendListener();

    void resumeListener();

    void terminateListener();

    boolean isListenerStarted();

    boolean isListenerSuspended();

    boolean isListenerResumed();

    boolean isListenerTerminated();

}
