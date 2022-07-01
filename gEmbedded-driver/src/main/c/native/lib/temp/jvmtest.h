#ifndef JVMTEST_H
#define JVMTEST_H

void testCreateJVM(void );
void testGetJNIEnv(void );
void testDestroyJVM(void );

#define JVM_TEST \
    CU_TestInfo jvmTests[] = { \
        { "testCreateJVM", testCreateJVM }, \
        { "testGetJNIEnv", testGetJNIEnv }, \
        { "testDestroyJVM", testDestroyJVM }, \
        CU_TEST_INFO_NULL }; \

#endif
