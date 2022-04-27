package com.comert.gEmbedded.api.device.common.validator;

import com.comert.gEmbedded.api.device.common.exception.InstanceCreationException;
import com.comert.gEmbedded.api.device.common.exception.ExceptionMessage;

import java.util.Arrays;

/**
 * Obje yaratılırken verilen sınıf içinde yaratılıp yaratılmadığını kontrol eder.
 * Factory harici obje yaratımını engellemek için tasarlanmıştır.
 */
public abstract class InstanceCreationValidator {

    private InstanceCreationValidator() {
    }

    public static void validateIfInstanceIsBeingCreatedInDesiredClass(final String fullQualifiedDesiredClassName) throws InstanceCreationException {
        final var result = Arrays.stream(Thread.currentThread().getStackTrace())
                .anyMatch(
                        stackTraceElement -> stackTraceElement
                                .getClassName()
                                .equals(fullQualifiedDesiredClassName)
                );
        if (!result)
            throw new InstanceCreationException(ExceptionMessage.INSTANCE_CREATED_OUT_OF_DESIRED_CLASS_MESSAGE, fullQualifiedDesiredClassName);
    }

}
