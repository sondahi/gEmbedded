#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>

#define MEMORY_FILE_NAME        ("/dev/mem")
#define PERIPHERAL_BASE_ADDRESS (0xFE000000)
#define CORE_CLOCK_SPEED        (1500000000)

typedef uint8_t u8_t;
typedef uint16_t u16_t;
typedef uint32_t u32_t;
typedef uint64_t u64_t;
typedef uintptr_t uPtr_t;

#endif