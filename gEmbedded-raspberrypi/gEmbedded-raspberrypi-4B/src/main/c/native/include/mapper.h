#ifndef MAPPER_H
#define MAPPER_H

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

#endif