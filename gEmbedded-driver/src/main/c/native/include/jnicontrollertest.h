#ifndef JNICONTROLLERTEST_H
#define JNICONTROLLERTEST_H

#include "jnicontroller.h"
#include "commontest.h"

int initJniControllerSuite (void);
int cleanupJniControllerSuite (void);

void testJniSetup(void );
void testGetConstantDigit(void );
void testGetConstantText(void );
void testThrowANewJNIException(void );
void testJniShutdown(void );


#define JNICONTROLLER_TEST \
    CU_TestInfo jniTests[] = { \
        { "testJniSetup", testJniSetup }, \
        { "testGetConstantDigit", testGetConstantDigit }, \
        { "testGetConstantText", testGetConstantText }, \
        { "testThrowANewJNIException", testThrowANewJNIException }, \
        { "testJniShutdown", testJniShutdown }, \
        CU_TEST_INFO_NULL }; \

#endif
