package com.comert.gEmbedded.api.device;

import com.comert.gEmbedded.api.device.impl.DeviceImpl;
import com.comert.gEmbedded.api.device.provider.ProviderFactory;

public abstract class DeviceFactory {

    private static DeviceImpl deviceProvider;

    private DeviceFactory() {
    }

    public static Device getDeviceInstance() {
        if (deviceProvider != null) {
            return deviceProvider;
        } else {
            synchronized (DeviceFactory.class) {
                if (deviceProvider != null) {
                    return deviceProvider;
                } else {
                    final var providerClassName = "com.comert.gEmbedded.api.device.impl.DeviceProvider";
                    final var providerParentClass = DeviceImpl.class;
                    deviceProvider = ProviderFactory.createProviderAndUpcastToParentReference(providerClassName, providerParentClass);
                    return deviceProvider;
                }
            }
        }
    }

}
