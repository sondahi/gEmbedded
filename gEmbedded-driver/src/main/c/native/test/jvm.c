#include "jvm.h"

JVM_STATUS createJVM(JavaVM **jvm, JNIEnv **env) {
    JavaVMOption javaVmOption[1];
    javaVmOption[0].optionString = "-Djava.class.path=/usr/lib/java:../../test";

    JavaVMInitArgs javaVmInitArgs;
    javaVmInitArgs.version = JNI_VERSION_10;
    javaVmInitArgs.nOptions = 1;
    javaVmInitArgs.options = javaVmOption;
    javaVmInitArgs.ignoreUnrecognized = JNI_FALSE;

    jint result = JNI_CreateJavaVM(&(*jvm), (void**) &(*env), &javaVmInitArgs);

    if (result != JNI_OK) {
        return JVM_UNSUCCESSFUL;
    }

    return JVM_SUCCESSFUL;
}

JVM_STATUS destroyJVM(JavaVM *jvm) {

    if(jvm == NULL){
        return JVM_UNSUCCESSFUL;
    } else{
        jint result = (*jvm)->DestroyJavaVM(jvm);
        if(result != JNI_OK){
            return JVM_UNSUCCESSFUL;
        }
    }

    return JVM_SUCCESSFUL;
}