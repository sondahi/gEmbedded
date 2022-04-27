package com.comert.gEmbedded.api.gpio.impl;

import com.comert.gEmbedded.api.device.common.exception.ExceptionMessage;
import com.comert.gEmbedded.api.device.Device;
import com.comert.gEmbedded.api.device.factory.DeviceFactory;
import com.comert.gEmbedded.api.device.gpio.factory.GPIOFactory;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestInstance;
import org.junit.jupiter.api.condition.EnabledOnJre;
import org.junit.jupiter.api.condition.JRE;

import static org.assertj.core.api.Assertions.assertThatExceptionOfType;
import static org.junit.jupiter.api.Assertions.assertDoesNotThrow;


@EnabledOnJre(JRE.JAVA_11)
@TestInstance(value = TestInstance.Lifecycle.PER_CLASS)
public class GPIOFactoryImplUTest {

    private Device device;

    @BeforeAll
    public void setUpTest(){
        device = DeviceFactory.getDeviceInstance();
        device.setUpDevice();
    }

    @AfterAll
    public void tearDownTest(){
        device.shutDownDevice();
    }

    @Test
    public void testFailWhenProviderIsBeingCreatedOutOfFactory() {
        final var desiredClassName = "com.gEmbedded.api.device.impl.DeviceImpl";

        assertThatExceptionOfType(RuntimeException.class)
                .isThrownBy(
                        GPIOFactoryProvider::new
                )
                .withMessage(ExceptionMessage.INSTANCE_CREATED_OUT_OF_DESIRED_CLASS_MESSAGE +" : "+desiredClassName);
    }

    @Test
    public void testSuccessWhenProviderIsBeingCreatedInFactoryClass() {
        assertDoesNotThrow(
                () -> DeviceFactory.getDeviceInstance().getGPIOFactoryInstance()
        );
    }

    @Test
    public void testPool(){
        Device device = DeviceFactory.getDeviceInstance();

        GPIOFactory factory = device.getGPIOFactoryInstance();

    }

}