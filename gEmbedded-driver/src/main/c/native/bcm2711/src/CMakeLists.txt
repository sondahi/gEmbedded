set(CMAKE_LIBRARY_OUTPUT_DIRECTORY /usr/lib)

add_library(${SHARED_LIB_NAME} SHARED
        ${SOURCE}
        gpiodriver.c
        i2cmasterdriver.c)