#include <CUnit/Basic.h>
#include "mappertest.h"
#include "jvmtest.h"

int main() {

    if (CUE_SUCCESS != CU_initialize_registry()){
        return CU_get_error();
    }

    MAPPER_TEST
    JVM_TEST

    CU_SuiteInfo suites[] = {
            { "MapperTest", NULL, NULL, NULL, NULL,mapperTests },
            { "JVMTest", NULL, NULL, NULL, NULL,jvmTests },
            CU_SUITE_INFO_NULL };

    CU_ErrorCode cuStatus = CU_register_suites (suites);

    if(cuStatus != CUE_SUCCESS){
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();

}

