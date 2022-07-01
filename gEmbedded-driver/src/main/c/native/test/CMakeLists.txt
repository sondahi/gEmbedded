include_directories(
        include
        ${JNI_INCLUDE_DIRS}
        /usr/include/CUnit)

set(TEST_SOURCE
        ${JNI_TEST_RESOURCES}
        src/main.c
        src/gpiodrivertest.c
        src/utils.S)

add_executable(test ${TEST_SOURCE})

target_link_libraries(test PUBLIC ${SHARED_LIB_NAME} ${JNI_LIBRARIES} cunit)