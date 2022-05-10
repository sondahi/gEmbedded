#ifndef JVM_H
#define JVM_H

#include <jni.h>

typedef enum JVM_STATUS_{
    JVM_SUCCESSFUL,
    JVM_UNSUCCESSFUL
} JVM_STATUS;

JVM_STATUS createJVM(JavaVM **jvm, JNIEnv **env);
JVM_STATUS destroyJVM(JavaVM *jvm);

#endif
