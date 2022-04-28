#include <CUnit/Basic.h>
#include <stdio.h>
#include "common.h"
#include "gpiotest.h"

extern void createJVM(void);

extern void destroyJVM(void);

extern int init_suite(void);

extern int clean_suite(void);

extern void testMapBaseRegister(void);

extern void testUnmapBaseRegister(void);

int main() {

    CU_pSuite pSuite = NULL;

    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /*
    pSuite = CU_add_suite("mappertest", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "testMapBaseRegister", testMapBaseRegister)) ||
        (NULL == CU_add_test(pSuite, "testUnmapBaseRegister", testUnmapBaseRegister))) {
        CU_cleanup_registry();
        return CU_get_error();
    }
     */

    pSuite = CU_add_suite("gpiotest", init_gpio_suite , clean_gpio_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "test1", testWrite))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();

}

