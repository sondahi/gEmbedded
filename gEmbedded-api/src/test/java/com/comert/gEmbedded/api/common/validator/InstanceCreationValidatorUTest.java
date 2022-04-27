package com.comert.gEmbedded.api.common.validator;

import com.comert.gEmbedded.api.device.common.exception.ExceptionMessage;
import com.comert.gEmbedded.api.device.common.exception.InstanceCreationException;
import com.comert.gEmbedded.api.device.common.validator.InstanceCreationValidator;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestInstance;
import org.junit.jupiter.api.condition.EnabledOnJre;
import org.junit.jupiter.api.condition.JRE;

import static org.assertj.core.api.Assertions.assertThatExceptionOfType;
import static org.junit.jupiter.api.Assertions.fail;


@EnabledOnJre(JRE.JAVA_11)
@TestInstance(value = TestInstance.Lifecycle.PER_CLASS)
public class InstanceCreationValidatorUTest {

    @Test
    public void testFailWhenInstanceIsBeingCreatedFromClassAnother() {
        final var notDesiredClass = "com.anotherpackage.AnotherClass";

        assertThatExceptionOfType(InstanceCreationException.class)
                .isThrownBy(
                        () -> InstanceCreationValidator.validateIfInstanceIsBeingCreatedInDesiredClass(notDesiredClass)
                )
                .withMessage(
                        ExceptionMessage.INSTANCE_CREATED_OUT_OF_DESIRED_CLASS_MESSAGE.toString() + " : " + notDesiredClass
                );
    }

    @Test
    public void testSuccesWhenInstanceIsBeingCreatedFromDesiredClass() {
        final String desiredClass = this.getClass().getName();

        try {
            InstanceCreationValidator.validateIfInstanceIsBeingCreatedInDesiredClass(desiredClass);
        } catch (InstanceCreationException instanceCreationException) {
            instanceCreationException.printStackTrace();
            fail("Exception should not be thrown");
        }
    }

}