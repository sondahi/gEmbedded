cmake_minimum_required(VERSION 3.18.4)

project(native C)

set(CMAKE_C_STANDARD 11)

find_package(JNI REQUIRED)

include_directories(
        ${JAVA_INCLUDE_PATH}
        ${JAVA_INCLUDE_PATH2}
        jni
        include)

SET(SHARED_LIB_NAME gEmbeddedRaspi4B32)

add_subdirectory(src)
add_subdirectory(test)