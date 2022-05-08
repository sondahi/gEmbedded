#ifndef MAPPERTEST_H
#define MAPPERTEST_H

#include "mapper.h"

void testFailMapWhenPhysicalAddressIsNotValid(void);

void testFailMapWhenBlockSizeIsNotValid(void);

void testFailMapWhenFileNameIsNotValid(void);

void testSuccessMapBaseRegister(void);

void testFailUnmapWhenBlockSizeIsNotValid(void);

void testFailUnmapWhenPointerIsNotValid(void);

void testSuccessUnmapBaseRegister(void);

#define MAPPER_TEST  \
    pSuite = CU_add_suite("MapperTest", NULL, NULL); \
    if (NULL == pSuite) { \
        CU_cleanup_registry(); \
        return CU_get_error(); \
    } \
    if (             \
        (NULL == CU_add_test(pSuite, "testFailMapWhenPhysicalAddressIsNotValid", testFailMapWhenPhysicalAddressIsNotValid)) || \
        (NULL == CU_add_test(pSuite, "testFailMapWhenBlockSizeIsNotValid", testFailMapWhenBlockSizeIsNotValid)) || \
        (NULL == CU_add_test(pSuite, "testFailMapWhenFileNameIsNotValid", testFailMapWhenFileNameIsNotValid)) || \
        (NULL == CU_add_test(pSuite, "testSuccessMapBaseRegister", testSuccessMapBaseRegister)) || \
        (NULL == CU_add_test(pSuite, "testFailUnmapWhenBlockSizeIsNotValid", testFailUnmapWhenBlockSizeIsNotValid)) || \
        (NULL == CU_add_test(pSuite, "testFailUnmapWhenPointerIsNotValid", testFailUnmapWhenPointerIsNotValid)) || \
        (NULL == CU_add_test(pSuite, "testSuccessUnmapBaseRegister", testSuccessUnmapBaseRegister)) \
) { \
        CU_cleanup_registry(); \
        return CU_get_error(); \
    }; \

#endif
