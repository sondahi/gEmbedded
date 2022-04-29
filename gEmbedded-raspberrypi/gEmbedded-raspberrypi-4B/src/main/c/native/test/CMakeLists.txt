include_directories(
        ${JNI_INCLUDE_DIRS}
        /usr/include/CUnit
        include
)

add_executable(test
        main.c
        jvm.c
        mappertest.c
        gpiotest.c include/mappertest.h)

target_link_libraries(test ${SHARED_LIB_NAME})
target_link_libraries(test cunit)
target_link_libraries(test ${JNI_LIBRARIES})