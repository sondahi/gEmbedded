package com.comert.gEmbedded.api.device.gpio.listener;

public interface GPIOEventListener {

    void onFalling();
    void onRising();
    void onTimeout();
    void onReadError();
    void onPollError();

}
