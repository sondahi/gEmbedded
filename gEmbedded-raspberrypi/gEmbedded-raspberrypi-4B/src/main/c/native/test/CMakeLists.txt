add_executable(test
        main.c
        jvm.c
        mappertest.c)

include_directories(
        ${JNI_INCLUDE_DIRS}
        /usr/include/CUnit
)

target_link_libraries(test gEmbeddedRasPi4B32)
target_link_libraries(test cunit)
target_link_libraries(test ${JNI_LIBRARIES})