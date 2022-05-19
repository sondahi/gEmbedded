set(CMAKE_LIBRARY_OUTPUT_DIRECTORY /usr/lib)

set(LIB_SOURCE
        src/device.c
        src/gpio.c
        src/i2cmaster.c
        src/i2cmaster_.c
        src/jninative.c
        src/mapper.c)

add_library(${SHARED_LIB_NAME} SHARED ${LIB_SOURCE})

target_include_directories(${SHARED_LIB_NAME} PUBLIC include)