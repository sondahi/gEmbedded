package com.comert.gEmbedded.api.device.provider;

import com.comert.gEmbedded.api.device.common.exception.ExceptionMessage;
import com.comert.gEmbedded.api.device.common.exception.ProviderException;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;

public abstract class ProviderFactory {

    private ProviderFactory() {
    }

    /*
     * Spesifikasyona göre provider belirlediğimiz hiyerarşiyi devralmak zorunda.
     * Sadece interface değil aynı zamanda birtakım kontroller için interface'i implement eden abstract sınıfıda implement etmelidir.
     * Private olan validasyon metodları istenilen şartları kontrol etmektedir.
     */
    public static <P> P createProviderAndUpcastToParentReference(final String fullQualifiedProviderClassName, final Class<P> providerParentClass) {
        P parentReference;
        try {
            Constructor<?> providerConstructor;
            Class<?> providerClass = validateIfProviderInDesiredPackageAndLoadProviderClass(fullQualifiedProviderClassName);
            validateIfProviderClassIsAChildClassOfDesiredClass(providerClass, providerParentClass);
            providerConstructor = validateIfProviderHasAPublicAndDefaultConstructorAndReturnConstructor(providerClass);
            parentReference = upCastProviderClassToParentReference(providerConstructor, providerParentClass);
        } catch (ProviderException exception) {
            throw new RuntimeException(exception.getMessage());
        }
        return parentReference;
    }

    private static Class<?> validateIfProviderInDesiredPackageAndLoadProviderClass(final String fullQualifiedProviderClassName) throws ProviderException {
        Class<?> providerClass;
        try {
            providerClass = Class.forName(fullQualifiedProviderClassName);
        } catch (ClassNotFoundException classNotFoundException) {
            throw new ProviderException(ExceptionMessage.PROVIDER_COULD_NOT_BE_FOUND_IN_IMPL_PACKAGE_MESSAGE, fullQualifiedProviderClassName);
        }
        return providerClass;
    }

    private static void validateIfProviderClassIsAChildClassOfDesiredClass(Class<?> providerClass, final Class<?> providerParentClass) throws ProviderException {
        if (providerClass.getSuperclass() != providerParentClass) {
            throw new ProviderException(ExceptionMessage.PROVIDER_DOES_NOT_IMPLEMENT_PARENT_CLASS_MESSAGE, providerClass.getName());
        }
    }

    private static Constructor<?> validateIfProviderHasAPublicAndDefaultConstructorAndReturnConstructor(Class<?> providerClass) throws ProviderException {
        Constructor<?> instanceCreator;
        try {
            instanceCreator = providerClass.getConstructor();
        } catch (NoSuchMethodException noSuchMethodException) {
            throw new ProviderException(ExceptionMessage.PROVIDER_DOES_NOT_HAVE_A_DEFAULT_CONSTRUCTOR_MESSAGE, providerClass.getName());
        }
        return instanceCreator;
    }

    private static <P> P upCastProviderClassToParentReference(Constructor<?> providerConstructor, final Class<P> providerParentClass) throws ProviderException {
        P parentReference;
        try {
            parentReference = providerParentClass.cast(providerConstructor.newInstance());
        } catch (InstantiationException | IllegalAccessException | InvocationTargetException e) {
            throw new ProviderException(ExceptionMessage.PROVIDER_COULD_NOT_BE_CONSTRUCTED_MESSAGE, providerConstructor.getName());
        }
        return parentReference;
    }

}
