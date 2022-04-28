include_directories(
        ${JNI_INCLUDE_DIRS}
        /usr/include/CUnit
        include
)

add_executable(test32
        main.c
        jvm.c
        mappertest.c
        gpiotest.c)

target_link_libraries(test32 ${LIB_32})
target_link_libraries(test32 cunit)
target_link_libraries(test32 ${JNI_LIBRARIES})

add_executable(test64
        main.c
        jvm.c
        mappertest.c
        gpiotest.c)

target_link_libraries(test64 ${LIB_64})
target_link_libraries(test64 cunit)
target_link_libraries(test64 ${JNI_LIBRARIES})