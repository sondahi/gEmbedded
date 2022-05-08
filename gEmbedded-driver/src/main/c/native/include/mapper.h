#ifndef MAPPER_H
#define MAPPER_H

#include <stddef.h>
#include <stdio.h>
#include <jni.h>

#define INVALID_PHYSICAL_ADDRESS    (0x0)
#define MIN_BLOCK_SIZE              (1)
#define MAX_BLOCK_SIZE              (4096)

typedef enum MAPPER_STATUS_{
    MAPPER_SUCCESS,
    MAPPER_PHYSICAL_ADDRESS_ERROR,
    MAPPER_BLOCK_SIZE_ERROR,
    MAPPER_FILE_NAME_ERROR,
    MAPPER_FILE_OPEN_ERROR,
    MAPPER_POINTER_ERROR,
    MAPPER_MEMORY_MAP_ERROR,
    MAPPER_MEMORY_UNMAP_ERROR
} MAPPER_STATUS;

MAPPER_STATUS mapBaseRegister (off_t physicalAddress, size_t blockSize, const char *fileName, void **pointer);

MAPPER_STATUS unmapBaseRegister (size_t blockSize, void *pointer);

#endif