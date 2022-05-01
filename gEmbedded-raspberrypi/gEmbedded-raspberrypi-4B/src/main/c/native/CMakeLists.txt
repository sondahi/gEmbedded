cmake_minimum_required(VERSION 3.18.4)

project(native ASM C)

set(CMAKE_C_STANDARD 11)

find_package(JNI REQUIRED)

include_directories(
        ${JAVA_INCLUDE_PATH}
        ${JAVA_INCLUDE_PATH2}
        include
)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    SET(LIBRARY_NAME gEmbeddedRaspi4B64)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    SET(LIBRARY_NAME gEmbeddedRaspi4B32)
endif()

SET(SHARED_LIB_NAME ${LIBRARY_NAME})

add_subdirectory(src)
add_subdirectory(test)