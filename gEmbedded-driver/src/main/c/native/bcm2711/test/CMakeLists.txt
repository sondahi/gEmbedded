include_directories(
        include
        ${JNI_INCLUDE_DIRS}
        /usr/include/CUnit)

set(TEST_SOURCE
        ${JNI_TEST_RESOURCES}
        src/gpiotest.c
        src/jninativetest.c
        src/jvm.c
        src/jvmtest.c
        src/main.c
        src/mappertest.c)

add_executable(test ${TEST_SOURCE})

target_link_libraries(test PUBLIC ${SHARED_LIB_NAME} ${JNI_LIBRARIES} cunit)