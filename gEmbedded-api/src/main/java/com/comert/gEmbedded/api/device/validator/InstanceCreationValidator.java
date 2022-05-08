package com.comert.gEmbedded.api.device.validator;

import com.comert.gEmbedded.api.device.exception.InstanceCreationException;
import com.comert.gEmbedded.api.device.exception.ExceptionMessage;

import java.util.Arrays;

public abstract class InstanceCreationValidator {

    private InstanceCreationValidator() {
    }

    public static void validateIfInstanceIsBeingCreatedInDesiredClass(final String fullQualifiedDesiredClassName) throws InstanceCreationException {
        final var result = Arrays
                .stream(Thread.currentThread().getStackTrace())
                .anyMatch(stackTraceElement -> stackTraceElement
                                .getClassName()
                                .equals(fullQualifiedDesiredClassName)
                );
        if (!result)
            throw new InstanceCreationException(ExceptionMessage.INSTANCE_CREATED_OUT_OF_DESIRED_CLASS_MESSAGE, fullQualifiedDesiredClassName);
    }

}
