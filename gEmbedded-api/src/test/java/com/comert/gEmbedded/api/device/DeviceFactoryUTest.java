package com.comert.gEmbedded.api.device;

import com.comert.gEmbedded.api.device.util.InstanceProducer;
import com.comert.gEmbedded.api.device.util.MultiThreadingTest;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestInstance;
import org.junit.jupiter.api.condition.EnabledForJreRange;
import org.junit.jupiter.api.condition.JRE;

import static org.junit.jupiter.api.Assertions.*;

@EnabledForJreRange(min = JRE.JAVA_17)
@TestInstance(value = TestInstance.Lifecycle.PER_CLASS)
public class DeviceFactoryUTest {

    @Test
    public void testSuccessInstanceIsNotNull() {
        assertNotNull(DeviceFactory.getDeviceInstance());
        assertInstanceOf(Device.class, DeviceFactory.getDeviceInstance());
    }

    @Test
    public void testSuccessInstancesAreSingleTon() {
        Device device1 = DeviceFactory.getDeviceInstance();
        Device device2 = DeviceFactory.getDeviceInstance();
        assertSame(device1, device2);
    }

    @Test
    public void testSuccessMultiThreadingAccess() throws InterruptedException {
        InstanceProducer<Device> deviceInstanceProducer = DeviceFactory::getDeviceInstance;

        int instanceSize = MultiThreadingTest.getInstanceSize(deviceInstanceProducer);
        assertEquals(1, instanceSize);
    }
}