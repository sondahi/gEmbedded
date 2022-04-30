#ifndef MAPPER_H
#define MAPPER_H

#include <stddef.h>
#include <stdio.h>

typedef enum MapperStatus_ {
    MAPPER_SUCCESS,
    MAPPER_PHYSICAL_ADDRESS_ERROR,
    MAPPER_BLOCK_SIZE_ERROR,
    MAPPER_FILE_NAME_ERROR,
    MAPPER_FILE_OPEN_ERROR,
    MAPPER_POINTER_ERROR,
    MAPPER_MEMORY_MAP_ERROR,
    MAPPER_MEMORY_UNMAP_ERROR
} MapperStatus;

MapperStatus mapBaseRegister (off_t physicalAddress, size_t blockSize, const char *fileName, void **pointer);

MapperStatus unmapBaseRegister (size_t blockSize, void *pointer);

#endif