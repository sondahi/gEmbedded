#ifndef MAPPERTEST_H
#define MAPPERTEST_H

#include "mapper.h"

void testMapBaseRegister(void);

void testUnmapBaseRegister(void);

#define MAPPER_TEST  \
    pSuite = CU_add_suite("MapperTest", NULL, NULL); \
    if (NULL == pSuite) { \
        CU_cleanup_registry(); \
        return CU_get_error(); \
    } \
    if ( \
        (NULL == CU_add_test(pSuite, "testMapBaseRegister", testMapBaseRegister)) || \
        (NULL == CU_add_test(pSuite, "testUnmapBaseRegister", testUnmapBaseRegister)) \
) { \
        CU_cleanup_registry(); \
        return CU_get_error(); \
    }; \

#endif
