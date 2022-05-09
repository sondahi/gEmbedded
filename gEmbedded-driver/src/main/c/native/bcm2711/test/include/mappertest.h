#ifndef MAPPERTEST_H
#define MAPPERTEST_H

#include "mapper.h"

void testMapBaseRegister (void);

void testUnmapBaseRegister (void);

#define MAPPER_TEST \
    CU_TestInfo mapperTests[] = { \
        { "testMapBaseRegister", testMapBaseRegister }, \
        { "testUnmapBaseRegister", testUnmapBaseRegister }, \
        CU_TEST_INFO_NULL }; \

#endif
