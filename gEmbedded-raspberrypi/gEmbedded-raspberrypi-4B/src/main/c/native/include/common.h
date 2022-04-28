#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <stdio.h>

#define MEMORY_FILE_NAME        ("/dev/mem")
#define PERIPHERAL_BASE_ADDRESS (0xFE000000)
#define CORE_CLOCK_SPEED        (1500000000)

typedef uint8_t u8;
typedef uint32_t reg_t;
typedef volatile reg_t reg;

#endif