#include <CUnit/Basic.h>
#include "mappertest.h"
#include "gpiotest.h"

int main() {

    if (CUE_SUCCESS != CU_initialize_registry()){
        return CU_get_error();
    }

    MAPPER_TEST
    GPIO_TEST

    CU_SuiteInfo suites[] = {
            { "MapperTest", NULL, NULL, NULL, NULL,mapperTests },
            { "GPIOTest", initGpioSuite, cleanupGpioSuite, NULL, NULL, gpioTests },
            CU_SUITE_INFO_NULL };

    CU_ErrorCode error = CU_register_suites (suites);

    if(error != CUE_SUCCESS){
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();

}

