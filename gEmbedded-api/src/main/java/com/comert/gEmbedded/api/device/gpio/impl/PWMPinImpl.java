package com.comert.gEmbedded.api.device.gpio.impl;

import com.comert.gEmbedded.api.device.exception.InstanceCreationException;
import com.comert.gEmbedded.api.device.validator.InstanceCreationValidator;
import com.comert.gEmbedded.api.device.gpio.pin.PWMPin;

// providerların bunu implemente etmesini zorlamalalı ama bu defa bütün metodların factoryde impl control edilmesi gerekiyor
// clienta sadece metodu uygulama sorumluluğu kalıyor. Yaratma kontrolü spefikasyon impl de olacak
// abstract adaptor
public abstract class PWMPinImpl implements PWMPin {

    protected PWMPinImpl() {
        synchronized (this) {
            final var desiredFactoryClassName = "com.comert.gEmbedded.api.gpio.impl.GPIOFactoryProvider";
            try {
                InstanceCreationValidator.validateIfInstanceIsBeingCreatedInDesiredClass(desiredFactoryClassName);
            } catch (InstanceCreationException instanceCreationException) {
                throw new RuntimeException(instanceCreationException.getMessage());
            }
        }

    }

}
