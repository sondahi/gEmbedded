cmake_minimum_required(VERSION 3.18.4)

project(native ASM C)

set(CMAKE_C_STANDARD 11)

#find_package(JNI REQUIRED)

#include_directories(
#        ${JAVA_INCLUDE_PATH}
#        ${JAVA_INCLUDE_PATH2}
#        ${CMAKE_CURRENT_SOURCE_DIR}/jni/include
#)

#SET(JNI_TEST_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/jni/com)

add_subdirectory(bcm2711)