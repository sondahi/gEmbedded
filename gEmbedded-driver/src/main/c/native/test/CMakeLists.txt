include_directories(
        ${JNI_INCLUDE_DIRS}
        /usr/include/CUnit)

set(JNI_RESOURCES com)

add_executable(test
        ${JNI_RESOURCES}
        main.c
        jvm.c
        mappertest.c
        gpiodrivertest.c jvmtest.c jnicontrollertest.c)

target_link_libraries(test ${SHARED_LIB_NAME})
target_link_libraries(test cunit)
target_link_libraries(test ${JNI_LIBRARIES})