#include <CUnit/Basic.h>
#include "gpiodrivertest.h"
#include "gpiodriver.h"

extern void delay(int time);
extern int add(int a1, int a2);


int main () {

    if (CUE_SUCCESS != CU_initialize_registry ()) {
        return CU_get_error ();
    }

    GPIO_DRIVER_TEST

    CU_SuiteInfo suites[] = {
            //{"JVMTest", NULL, NULL, NULL, NULL, jvmTests},
            //{"JniControllerTest", initJniControllerSuite, cleanupJniControllerSuite, NULL, NULL, jniTests},
            //{"MapperTest", NULL, NULL, NULL, NULL, mapperTests},
            {"GPIO_DRIVER_TEST", initGPIODriverSuite, cleanupGPIODriverSuite, NULL, NULL, gpioDriverTests},
            CU_SUITE_INFO_NULL};

    CU_ErrorCode cuStatus = CU_register_suites (suites);
    if (cuStatus != CUE_SUCCESS) {
        CU_cleanup_registry ();
        return CU_get_error ();
    }

    CU_basic_set_mode (CU_BRM_VERBOSE);

    //createJVM();
    CU_basic_run_tests ();
    //destroyJVM();

    CU_cleanup_registry ();
    return CU_get_error ();

}

