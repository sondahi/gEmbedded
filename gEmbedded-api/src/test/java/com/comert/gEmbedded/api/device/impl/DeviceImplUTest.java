package com.comert.gEmbedded.api.device.impl;

import com.comert.gEmbedded.api.device.common.exception.ExceptionMessage;
import com.comert.gEmbedded.api.device.Device;
import com.comert.gEmbedded.api.device.factory.DeviceFactory;
import com.comert.gEmbedded.api.device.gpio.factory.GPIOFactory;
import com.comert.gEmbedded.api.gpio.impl.GPIOFactoryProvider;
import com.comert.gEmbedded.api.util.device.InstanceProcuder;
import com.comert.gEmbedded.api.util.device.MultiThreadingTest;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestInstance;
import org.junit.jupiter.api.condition.EnabledOnJre;
import org.junit.jupiter.api.condition.JRE;

import static org.assertj.core.api.Assertions.assertThatExceptionOfType;
import static org.junit.jupiter.api.Assertions.*;


@EnabledOnJre(JRE.JAVA_11)
@TestInstance(value = TestInstance.Lifecycle.PER_CLASS)
public class DeviceImplUTest {

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
    public void testFailWhenDeviceProviderIsBeingCreatedOutOfFactory() {
        final var desiredClassName = "com.gEmbedded.api.device.factory.DeviceFactory";

        assertThatExceptionOfType(RuntimeException.class)
                .isThrownBy(
                        DeviceProvider::new
                )
                .withMessage(ExceptionMessage.INSTANCE_CREATED_OUT_OF_DESIRED_CLASS_MESSAGE +" : "+desiredClassName);
    }

    @Test
    public void testSuccessWhenProviderIsBeingCreatedInFactoryClass() {
        assertDoesNotThrow(
                DeviceFactory::getDeviceInstance
        );
    }

    @Test
    public void testSuccesWhenGetGPIOFactory() {
        GPIOFactory factory = device.getGPIOFactoryInstance();
        assertNotNull(factory);
        assertEquals(GPIOFactoryProvider.class, factory.getClass());
    }

    @Test
    public void testSuccesGPIOFactorySingleTonInstance() {
        GPIOFactory factory1 = device.getGPIOFactoryInstance();
        GPIOFactory factory2 = device.getGPIOFactoryInstance();
        assertSame(factory1, factory2);
        assertEquals(factory1, factory2);
    }

    @Test
    public void testSuccesGPIOFactorySingleTonMultiThreadingAccsess() throws InterruptedException {
        InstanceProcuder<GPIOFactory> gpioFactoryInstanceProcuder = device::getGPIOFactoryInstance;

        int instanceSize = MultiThreadingTest.instanceSize(gpioFactoryInstanceProcuder);
        assertEquals(1, instanceSize);
    }

}