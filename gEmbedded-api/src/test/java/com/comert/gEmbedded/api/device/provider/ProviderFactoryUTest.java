package com.comert.gEmbedded.api.device.provider;

import com.comert.gEmbedded.api.device.exception.ExceptionMessage;
import com.comert.gEmbedded.api.device.util.TestParentImpl;
import com.comert.gEmbedded.api.device.util.TestValidProvider;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestInstance;
import org.junit.jupiter.api.condition.EnabledForJreRange;
import org.junit.jupiter.api.condition.EnabledOnJre;
import org.junit.jupiter.api.condition.JRE;

import static org.assertj.core.api.Assertions.assertThatExceptionOfType;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;

@EnabledForJreRange(min = JRE.JAVA_17)
@TestInstance(value = TestInstance.Lifecycle.PER_CLASS)
public class ProviderFactoryUTest {

    private final String implPackage = "com.comert.gEmbedded.api.device.util.";
    private final Class<TestParentImpl> parentClass = TestParentImpl.class;

    @Test
    public void testFailWhenProviderIsNotInThePackage() {
        final var invalidProviderClassName = implPackage + "ThereIsNoProviderClassInPackage";

        assertThatExceptionOfType(RuntimeException.class)
                .isThrownBy(
                        () -> ProviderFactory.createProviderAndUpcastToParentReference(invalidProviderClassName, parentClass)
                )
                .withMessage(
                        ExceptionMessage.PROVIDER_COULD_NOT_BE_FOUND_IN_IMPL_PACKAGE_MESSAGE + " : " + invalidProviderClassName
                );
    }

    @Test
    public void testFailWhenProviderIsNotAChildClass() {
        final var invalidProviderClassName = implPackage + "TestInvalidProvider1";

        assertThatExceptionOfType(RuntimeException.class)
                .isThrownBy(
                        () -> ProviderFactory.createProviderAndUpcastToParentReference(invalidProviderClassName, parentClass)
                )
                .withMessage(
                        ExceptionMessage.PROVIDER_DOES_NOT_IMPLEMENT_PARENT_CLASS_MESSAGE + " : " + invalidProviderClassName
                );
    }

    @Test
    public void testFailWhenProviderDoesNotHaveAPublicDefaultConstructor() {
        final var invalidProviderClassName = implPackage + "TestInvalidProvider2";

        assertThatExceptionOfType(RuntimeException.class)
                .isThrownBy(
                        () -> ProviderFactory.createProviderAndUpcastToParentReference(invalidProviderClassName, parentClass)
                )
                .withMessage(
                        ExceptionMessage.PROVIDER_DOES_NOT_HAVE_A_DEFAULT_CONSTRUCTOR_MESSAGE + " : " + invalidProviderClassName
                );
    }

    @Test
    public void testSuccessWhenInstanceIsBeingCreated() {
        final var validProviderClassName = implPackage + "TestValidProvider";

        TestParentImpl toReferenceParentClass = ProviderFactory.createProviderAndUpcastToParentReference(validProviderClassName, parentClass);

        assertNotNull(toReferenceParentClass);
        assertEquals(TestValidProvider.class, toReferenceParentClass.getClass());
        assertEquals(TestParentImpl.class, toReferenceParentClass.getClass().getSuperclass());
    }

}