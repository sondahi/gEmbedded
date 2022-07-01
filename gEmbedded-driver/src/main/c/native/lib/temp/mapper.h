/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   mapper.h
 * Author: Gökay Cömert
 *
 * Created on 17. April 2022, 23:04
 */

#ifndef MAPPER_H
#define MAPPER_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include <stddef.h>
#include <fcntl.h>
    
    typedef enum MapperStatus_ {
        MAPPER_SUCCESS,
        MAPPER_FILE_OPEN_ERROR,
        MAPPER_MEMORY_MAP_ERROR,
        MAPPER_MEMORY_UNMAP_ERROR
    } MapperStatus;

    MapperStatus mapBaseRegister(void **pointer, const char *fileName, size_t blockSize, off_t physicalAddress);
    MapperStatus unmapBaseRegister(void *pointer, size_t blockSize);

#ifdef __cplusplus
}
#endif

#endif /* MAPPER_H */