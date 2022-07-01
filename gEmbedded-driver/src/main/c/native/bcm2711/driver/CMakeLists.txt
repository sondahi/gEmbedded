include_directories(
        include
        include/system
)

set(DRIVER_SOURCES
        src/gpiodriver.c)

add_library(${SHARED_LIB_NAME} SHARED ${DRIVER_SOURCES})