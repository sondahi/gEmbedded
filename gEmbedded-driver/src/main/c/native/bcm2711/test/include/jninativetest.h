#ifndef JNINATIVETEST_H
#define JNINATIVETEST_H

#include "commontest.h"

int initJniControllerSuite (void);
int cleanupJniControllerSuite (void);

void testJniSetup(void );
void testGetEnumDigit(void );
void testGetEnumText(void );
void testThrowANewJNIException(void );
void testJniShutdown(void );


#define JNICONTROLLER_TEST \
    CU_TestInfo jniTests[] = { \
        { "testJniSetup", testJniSetup }, \
        { "testGetEnumDigit", testGetEnumDigit }, \
        { "testGetEnumText", testGetEnumText }, \
        { "testThrowANewJNIException", testThrowANewJNIException }, \
        { "testJniShutdown", testJniShutdown }, \
        CU_TEST_INFO_NULL }; \

#endif
