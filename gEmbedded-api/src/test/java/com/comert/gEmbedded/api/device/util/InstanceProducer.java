package com.comert.gEmbedded.api.device.util;

import org.junit.jupiter.api.Disabled;

@Disabled
@FunctionalInterface
public interface InstanceProducer<I> {
    I getInstance();
}
