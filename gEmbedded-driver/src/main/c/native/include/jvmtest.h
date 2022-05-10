#ifndef JVMTEST_H
#define JVMTEST_H

#include "jvm.h"

void testCreateJVM(void );
void testDestroyJVM(void );

#define JVM_TEST \
    CU_TestInfo jvmTests[] = { \
        { "testCreateJVM", testCreateJVM }, \
        { "testDestroyJVM", testDestroyJVM }, \
        CU_TEST_INFO_NULL }; \

#endif
