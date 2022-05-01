set(CMAKE_LIBRARY_OUTPUT_DIRECTORY /usr/lib)

add_library(${SHARED_LIB_NAME} SHARED
        devicecontroller.c
        gpiocontroller.c
        gpiodriver.c
        i2cmastercontroller.c
        i2cmasterdriver.c
        jnicontroller.c
        mapper.c)
