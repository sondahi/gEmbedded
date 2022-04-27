#ifndef COMMON_H
#define COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include <stdio.h>

#define MEMORY_FILE_NAME        ("/dev/mem")
#define PERIPHERAL_BASE_ADDRESS (0xFE000000)
#define CORE_CLOCK_SPEED        (1500000000)

#if __WORDSIZE == 32
    # define REGISTER_TYPE		unsigned int
#elif __WORDSIZE == 64
    # define REGISTER_TYPE		unsigned long
#else
    # error
#endif

typedef uint8_t u8;
typedef uint32_t u32;
typedef volatile u8 vu8;
typedef volatile REGISTER_TYPE reg;

#ifdef __cplusplus
}
#endif

#endif /* COMMON_H */