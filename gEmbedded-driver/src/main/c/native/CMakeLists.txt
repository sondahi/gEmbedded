cmake_minimum_required(VERSION 3.18.4)

project(native ASM C)

set(CMAKE_C_STANDARD 11)

find_package(JNI REQUIRED)

include_directories(
        ${JAVA_INCLUDE_PATH}
        ${JAVA_INCLUDE_PATH2}
        jni/include
)

set(SOURCE
        ${CMAKE_CURRENT_SOURCE_DIR}/jni/src/devicecontroller.c
        ${CMAKE_CURRENT_SOURCE_DIR}/jni/src/jnicontroller.c
        ${CMAKE_CURRENT_SOURCE_DIR}/jni/src/mapper.c
        ${CMAKE_CURRENT_SOURCE_DIR}/jni/src/gpiocontroller.c
        ${CMAKE_CURRENT_SOURCE_DIR}/jni/src/i2cmastercontroller.c)

add_subdirectory(bcm2711)