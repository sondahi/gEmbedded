package com.comert.gEmbedded.api.device.factory;

import com.comert.gEmbedded.api.device.Device;
import com.comert.gEmbedded.api.util.device.InstanceProcuder;
import com.comert.gEmbedded.api.util.device.MultiThreadingTest;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestInstance;
import org.junit.jupiter.api.condition.EnabledOnJre;
import org.junit.jupiter.api.condition.JRE;

import static org.junit.jupiter.api.Assertions.*;


@EnabledOnJre(JRE.JAVA_11)
@TestInstance(value = TestInstance.Lifecycle.PER_CLASS)
public class DeviceFactoryUTest {

    @Test
    public void testSuccesInstanceIsNotNull(){
        assertNotNull(DeviceFactory.getDeviceInstance());
    }

    @Test
    public void testSuccesInstancesAreSingleTon(){
        Device device1 = DeviceFactory.getDeviceInstance();
        Device device2 = DeviceFactory.getDeviceInstance();
        assertSame(device1, device2);
    }

    @Test
    public void testSuccesMultiThreadingAccess() throws InterruptedException {
        InstanceProcuder<Device> deviceInstanceProcuder = DeviceFactory::getDeviceInstance;

        int instanceSize = MultiThreadingTest.instanceSize(deviceInstanceProcuder);
        assertEquals(1,instanceSize);
    }
}