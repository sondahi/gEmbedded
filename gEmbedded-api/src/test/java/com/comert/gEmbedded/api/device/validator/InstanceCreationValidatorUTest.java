package com.comert.gEmbedded.api.device.validator;

import com.comert.gEmbedded.api.device.exception.ExceptionMessage;
import com.comert.gEmbedded.api.device.exception.InstanceCreationException;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestInstance;
import org.junit.jupiter.api.condition.EnabledForJreRange;
import org.junit.jupiter.api.condition.JRE;

import static org.assertj.core.api.Assertions.assertThatExceptionOfType;
import static org.junit.jupiter.api.Assertions.fail;


@EnabledForJreRange(min = JRE.JAVA_17)
@TestInstance(value = TestInstance.Lifecycle.PER_CLASS)
public class InstanceCreationValidatorUTest {

    @Test
    public void testFailWhenInstanceIsBeingCreatedOutOfDesiredClass() {
        final var notDesiredClass = "com.anotherpackage.AnotherClass";

        assertThatExceptionOfType(InstanceCreationException.class)
                .isThrownBy(
                        () -> InstanceCreationValidator.validateIfInstanceIsBeingCreatedInDesiredClass(notDesiredClass)
                )
                .withMessage(
                        ExceptionMessage.INSTANCE_CREATED_OUT_OF_DESIRED_CLASS_MESSAGE + " : " + notDesiredClass
                );
    }

    @Test
    public void testSuccessWhenInstanceIsBeingCreatedInDesiredClass() {
        final String desiredClass = this.getClass().getName();

        try {
            InstanceCreationValidator.validateIfInstanceIsBeingCreatedInDesiredClass(desiredClass);
        } catch (InstanceCreationException instanceCreationException) {
            instanceCreationException.printStackTrace();
            fail("Exception should not be thrown");
        }
    }

}