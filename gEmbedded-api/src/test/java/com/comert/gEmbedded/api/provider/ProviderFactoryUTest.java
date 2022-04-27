package com.comert.gEmbedded.api.provider;

import com.comert.gEmbedded.api.device.common.exception.ExceptionMessage;
import com.comert.gEmbedded.api.device.provider.ProviderFactory;
import com.comert.gEmbedded.api.util.provider.TestParentImpl;
import com.comert.gEmbedded.api.util.provider.TestValidProvider;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestInstance;
import org.junit.jupiter.api.condition.EnabledOnJre;
import org.junit.jupiter.api.condition.JRE;

import static org.assertj.core.api.Assertions.assertThatExceptionOfType;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;


@EnabledOnJre(JRE.JAVA_11)
@TestInstance(value = TestInstance.Lifecycle.PER_CLASS)
public class ProviderFactoryUTest {

    private final String implPackage = "com.gEmbedded.api.util.provider.";
    private final Class<TestParentImpl> parentClass = TestParentImpl.class;

    @Test
    public void testFailWhenProviderIsNotInThePackage() {
        final var invalidProviderClassName = implPackage + "ThereIsNoProviderClass";

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
                        ExceptionMessage.PROVIDER_DOES_NOT_IMPLEMENT_PARENT_CLASS_MESSAGE.toString() + " : " + invalidProviderClassName
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
    public void testSuccesWhenInstanceIsBeingCreated() {
        final var validProviderClassName = implPackage + "TestValidProvider";

        TestParentImpl toReferenceParentClass = ProviderFactory.createProviderAndUpcastToParentReference(validProviderClassName, parentClass);

        assertNotNull(toReferenceParentClass);
        assertEquals(TestValidProvider.class, toReferenceParentClass.getClass());
        assertEquals(TestParentImpl.class, toReferenceParentClass.getClass().getSuperclass());
    }

}