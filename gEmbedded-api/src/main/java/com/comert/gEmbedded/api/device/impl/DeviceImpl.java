package com.comert.gEmbedded.api.device.impl;

import com.comert.gEmbedded.api.device.Device;
import com.comert.gEmbedded.api.device.exception.DeviceExecutionException;
import com.comert.gEmbedded.api.device.exception.ExceptionMessage;
import com.comert.gEmbedded.api.device.exception.InstanceCreationException;
import com.comert.gEmbedded.api.device.validator.InstanceCreationValidator;
import com.comert.gEmbedded.api.device.provider.ProviderFactory;
import com.comert.gEmbedded.api.device.gpio.GPIOFactory;
import com.comert.gEmbedded.api.device.gpio.impl.GPIOFactoryImpl;
import com.comert.gEmbedded.api.device.i2c.I2CMasterFactory;
import com.comert.gEmbedded.api.device.i2c.impl.I2CMasterFactoryImpl;

public abstract class DeviceImpl implements Device {

    private static GPIOFactoryImpl GPIOFactoryProvider;
    private static I2CMasterFactoryImpl I2CMasterFactoryProvider;

    private boolean deviceExecuting;

    protected DeviceImpl() {
        synchronized (this) {
            final var desiredFactoryClassName = "com.comert.gEmbedded.api.device.DeviceFactory";
            try {
                InstanceCreationValidator.validateIfInstanceIsBeingCreatedInDesiredClass(desiredFactoryClassName);
            } catch (InstanceCreationException instanceCreationException) {
                throw new RuntimeException(instanceCreationException.getMessage());
            }
        }
    }

    @Override
    public final synchronized void setUpDevice() {
        if (deviceExecuting) {
            try {
                throw new DeviceExecutionException(ExceptionMessage.DEVICE_IS_ALREADY_SET_UP_MESSAGE, "RaspberryPi");
            } catch (DeviceExecutionException deviceExecutionException) {
                throw new RuntimeException(deviceExecutionException.getMessage());
            }
        } else {
            executeSetUp();
            deviceExecuting = true;
        }
    }

    @Override
    public final synchronized void shutDownDevice() {
        if (deviceExecuting) {
            executeShutDown();
            deviceExecuting = false;
        } else {
            try {
                throw new DeviceExecutionException(ExceptionMessage.DEVICE_IS_ALREADY_SHUT_DOWN_MESSAGE, "RaspberryPi");
            } catch (DeviceExecutionException deviceExecutionException) {
                throw new RuntimeException(deviceExecutionException.getMessage());
            }
        }
    }

    protected abstract void executeSetUp();

    protected abstract void executeShutDown();

    @Override
    public synchronized final GPIOFactory getGPIOFactoryInstance() {
        if (!deviceExecuting)
            try {
                throw new DeviceExecutionException(ExceptionMessage.DEVICE_MUST_BE_SETUP_MESSAGE, "RaspberryPi");
            } catch (DeviceExecutionException deviceExecutionException) {
                throw new RuntimeException(deviceExecutionException.getMessage());
            }
        if (GPIOFactoryProvider != null) {
            return GPIOFactoryProvider;
        } else {
            final var providerClassName = "com.comert.gEmbedded.api.gpio.impl.GPIOFactoryProvider";
            final var providerParentClass = GPIOFactoryImpl.class;
            GPIOFactoryProvider = ProviderFactory.createProviderAndUpcastToParentReference(providerClassName, providerParentClass);
            return GPIOFactoryProvider;
        }
    }

    @Override
    public synchronized final I2CMasterFactory getI2CMasterFactoryInstance() {
        if (!deviceExecuting)
            try {
                throw new DeviceExecutionException(ExceptionMessage.DEVICE_MUST_BE_SETUP_MESSAGE, "RaspberryPi");
            } catch (DeviceExecutionException deviceExecutionException) {
                throw new RuntimeException(deviceExecutionException.getMessage());
            }
        if (I2CMasterFactoryProvider != null) {
            return I2CMasterFactoryProvider;
        } else {
            final var providerClassName = "com.comert.gEmbedded.api.i2c.impl.I2CMasterFactoryProvider";
            final var providerParentClass = I2CMasterFactoryImpl.class;
            I2CMasterFactoryProvider = ProviderFactory.createProviderAndUpcastToParentReference(providerClassName, providerParentClass);
            return I2CMasterFactoryProvider;
        }
    }
}
