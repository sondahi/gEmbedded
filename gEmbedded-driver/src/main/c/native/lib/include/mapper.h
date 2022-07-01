#ifndef MAPPER_H
#define MAPPER_H

#include <stddef.h>
#include <stdio.h>

typedef enum MAPPER_STATUS_{
    MAPPER_SUCCESS,
    MAPPER_ERROR
} MAPPER_STATUS;

MAPPER_STATUS mapBaseRegister (const char *fileName, size_t blockSize, off_t physicalAddress, void **pointer);

MAPPER_STATUS unmapBaseRegister (void *pointer, size_t blockSize);

#endif