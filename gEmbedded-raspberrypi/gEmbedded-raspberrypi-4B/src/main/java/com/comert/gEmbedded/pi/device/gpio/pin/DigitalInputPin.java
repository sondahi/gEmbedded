package com.comert.gEmbedded.pi.device.gpio.pin;

import com.comert.gEmbedded.api.device.common.exception.ExceptionMessage;
import com.comert.gEmbedded.api.device.common.exception.InstanceIsNotCreatedException;
import com.comert.gEmbedded.api.device.gpio.impl.InPutPinImpl;
import com.comert.gEmbedded.api.device.gpio.listener.GPIOEventListener;
import com.comert.gEmbedded.api.device.gpio.pin.*;
import com.comert.gEmbedded.api.device.gpio.pin.configurator.InPutPinConfigurator;
import com.comert.gEmbedded.pi.nativeinterface.GPIOController;

import java.util.HashMap;
import java.util.Map;
import java.util.Optional;


public final class DigitalInputPin extends InPutPinImpl {

    private static final Map<Pin, InPutPin> createdDigitalInPutPins = new HashMap<>(); // analog olursa yukarı al

    private final Pin pin;
    private final PinType pinType;
    private final PullUpDownStatus pullUpDownStatus;
    private final GPIOEventListener GPIOEventListener;
    private final EventDetectStatus eventDetectStatus;
    private final int eventTimeout;

    private final int pinNumber;
    private final int registerSelector;
    private final int pinSet;

    private final Thread gpioEventWorker;
    private volatile boolean running;
    private volatile boolean suspended;

    public DigitalInputPin(InPutPinConfigurator inPutPinConfigurator) {
        pin = inPutPinConfigurator.getPin();
        pinType = inPutPinConfigurator.getPinType();
        pullUpDownStatus = inPutPinConfigurator.getPullUpDownStatus();
        GPIOEventListener = inPutPinConfigurator.getEventListener();
        eventDetectStatus = inPutPinConfigurator.getEventDetectStatus();
        eventTimeout = inPutPinConfigurator.getEventTimeout();

        this.pinNumber = pin.getDigit();
        this.registerSelector = (pin.getDigit() / 32);
        this.pinSet = (1 << (pin.getDigit() % 32));

        gpioEventWorker = new GPIOEventWorker();

        createdDigitalInPutPins.put(pin, this);
    }

    private class GPIOEventWorker extends Thread {

        @Override
        public void run() {
            while (running) {
                while (suspended) {
                    try {
                        wait();
                    } catch (InterruptedException interruptedException) {
                        //handle if interrupted and suspended wait for not suspended
                    }
                }
                int result = GPIOController.poll(pinNumber, eventTimeout);
                if (running & !suspended) { // double check because of timeout. maybe thread is terminated or suspended
                    switch (result) {
                        case 0: {
                            GPIOEventListener.onFalling();
                            break;
                        }
                        case 1: {
                            GPIOEventListener.onRising();
                            break;
                        }
                        case 2: {
                            GPIOEventListener.onReadError();
                            break;
                        }
                        case 3: {
                            GPIOEventListener.onTimeout();
                            break;
                        }
                        default: {
                            GPIOEventListener.onPollError();
                            break;
                        }
                    }
                }

            }
            GPIOController.releaseGPIOThreadRecourse(pinNumber);
        }
    }

    public InPutPin getInstanceIfExist(Pin pin) {
        if (createdDigitalInPutPins.containsKey(pin)) {
            return createdDigitalInPutPins.get(pin);
        } else {
            try {
                throw new InstanceIsNotCreatedException(ExceptionMessage.INSTANCE_IS_NOT_CREATED_MESSAGE, pin.getText());
            } catch (InstanceIsNotCreatedException InstanceIsNotCreatedException) {
                throw new RuntimeException(InstanceIsNotCreatedException.getMessage());
            }
        }
    }

    @Override
    public Pin getPin() {
        return pin;
    }

    @Override
    public PinType getPinType() {
        return pinType;
    }

    @Override
    public PullUpDownStatus getPullUpDownStatus() {
        return pullUpDownStatus;
    }

    @Override
    public EventDetectStatus getEventDetectStatus() {
        return eventDetectStatus;
    }

    @Override
    public int getEventTimeout() {
        return eventTimeout;
    }

    @Override
    public Optional<GPIOEventListener> getEventListener() {
        return Optional.ofNullable(GPIOEventListener);
    }

    @Override
    public boolean isLow() {
        return GPIOController.isLow(registerSelector, pinSet);
    }

    @Override
    public boolean isHigh() {
        return GPIOController.isHigh(registerSelector, pinSet);
    }

    @Override
    public double read() {
        return GPIOController.isHigh(registerSelector, pinSet) ? 5.0 : 0.0;
    }

    @Override
    public synchronized void startListener() {
        if (running)
            throw new RuntimeException("Listener is already activated"); // change it
        running = true;
        gpioEventWorker.start();
    }

    @Override
    public synchronized void suspendListener() {
        if (running) {
            suspended = true;
        } else {
            throw new RuntimeException("listener terminated");
        }
    }

    @Override
    public synchronized void resumeListener() {
        if (running) {
            suspended = false;
            notify();
        } else {
            throw new RuntimeException("listener terminated");
        }
    }

    @Override
    public synchronized void terminateListener() {
        if (!running)
            throw new RuntimeException("Listener is already terminated"); // change it
        running = false;
        notify(); // maybe suspended
        try {
            gpioEventWorker.join();
        } catch (InterruptedException interruptedException) {
            // do something maybe release sources
        }
    }

    @Override
    public synchronized boolean isListenerStarted() {
        return running;
    }

    @Override
    public synchronized boolean isListenerSuspended() {
        return suspended;
    }

    @Override
    public synchronized boolean isListenerResumed() {
        return !suspended;
    }

    @Override
    public synchronized boolean isListenerTerminated() {
        return !running;
    }

}
