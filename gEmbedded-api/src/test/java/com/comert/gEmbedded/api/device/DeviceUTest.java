package com.comert.gEmbedded.api.device;

import com.comert.gEmbedded.api.device.factory.DeviceFactory;
import com.comert.gEmbedded.api.device.gpio.factory.GPIOFactory;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestInstance;
import org.junit.jupiter.api.condition.EnabledOnJre;
import org.junit.jupiter.api.condition.JRE;

import static org.junit.jupiter.api.Assertions.assertNotNull;


@EnabledOnJre(JRE.JAVA_11)
@TestInstance(value = TestInstance.Lifecycle.PER_CLASS)public class DeviceUTest {

    @Test
    public void testSuccessWhenDeviceshutDown() {
        Device device = DeviceFactory.getDeviceInstance();
        device.setUpDevice();

        device.shutDownDevice();
    }

    @Test
    public void testSuccessWhenGPIOFactoryCreated() {
        Device device = DeviceFactory.getDeviceInstance();
        device.setUpDevice();
        GPIOFactory factory = device.getGPIOFactoryInstance();

        assertNotNull(factory);
        device.shutDownDevice();
    }

}