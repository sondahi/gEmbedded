#include <CUnit/Basic.h>
#include "jvm.h"
#include "mappertest.h"
#include "jvmtest.h"
#include "jninativetest.h"

int main () {

    if (CUE_SUCCESS != CU_initialize_registry ()) {
        return CU_get_error ();
    }

    JVM_TEST
    JNICONTROLLER_TEST
    MAPPER_TEST

    CU_SuiteInfo suites[] = {
            //{"JVMTest", NULL, NULL, NULL, NULL, jvmTests},
            //{"JniControllerTest", initJniControllerSuite, cleanupJniControllerSuite, NULL, NULL, jniTests},
            {"MapperTest", NULL, NULL, NULL, NULL, mapperTests},
            CU_SUITE_INFO_NULL};

    CU_ErrorCode cuStatus = CU_register_suites (suites);
    if (cuStatus != CUE_SUCCESS) {
        CU_cleanup_registry ();
        return CU_get_error ();
    }

    CU_basic_set_mode (CU_BRM_VERBOSE);

    createJVM();
    CU_basic_run_tests ();
    destroyJVM();

    CU_cleanup_registry ();
    return CU_get_error ();

}

