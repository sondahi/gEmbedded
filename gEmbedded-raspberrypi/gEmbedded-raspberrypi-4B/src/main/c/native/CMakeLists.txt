cmake_minimum_required(VERSION 3.18.4)

project(native ASM C)

set(CMAKE_C_STANDARD 11)

find_package(JNI REQUIRED)

include_directories(
        ${JAVA_INCLUDE_PATH}
        ${JAVA_INCLUDE_PATH2}
        include
)

SET(LIB_32 gEmbeddedRasPi4B32)
SET(LIB_64 gEmbeddedRasPi4B64)

IF(${CMAKE_SYSTEM_PROCESSOR} MATCHES "armv7l")
    SET(SHARED_LIBRARY_NAME ${LIB_32})
ELSE()
    SET(SHARED_LIBRARY_NAME ${LIB_64})
ENDIF()

add_subdirectory(src)
add_subdirectory(test)