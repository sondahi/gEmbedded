#ifndef JVM_H
#define JVM_H

#include <jni.h>

typedef enum JVM_STATUS_{
    JVM_SUCCESS,
    JVM_UNSUCCESS
} JVM_STATUS;

JVM_STATUS createJVM();
JVM_STATUS getJNIEnv(JNIEnv **jniEnv);
JVM_STATUS destroyJVM();

#endif
