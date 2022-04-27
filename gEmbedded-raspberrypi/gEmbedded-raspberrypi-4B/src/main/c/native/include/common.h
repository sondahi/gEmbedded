/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   common.h
 * Author: Gökay Cömert
 *
 * Created on 17. April 2022, 22:22
 */

#ifndef COMMON_H
#define COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define MEMORY_FILE_NAME        ("/dev/mem")
#define PERIPHERAL_BASE_ADDRESS (0xFE000000)
#define CORE_CLOCK_SPEED        (1500000000)

    typedef uint8_t u8;
    typedef uint16_t u16;
    typedef uint32_t u32;
    typedef uint64_t u64;

    typedef volatile u8 vu8;
    typedef volatile u32 reg;

#ifdef __cplusplus
}
#endif

#endif /* COMMON_H */