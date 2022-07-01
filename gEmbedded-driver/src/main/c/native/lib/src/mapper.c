#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include "mapper.h"

MAPPER_STATUS
mapBaseRegister (const char *fileName, const size_t blockSize, const off_t physicalAddress, void **pointer) {

    if (fileName == NULL || blockSize == 0) { /* || physicalAddress < 0){*/
        return MAPPER_ERROR;
    }

    const int memoryFileDescriptor = open (fileName, O_RDWR | O_SYNC);

    if (memoryFileDescriptor < 0) {
        close (memoryFileDescriptor);
        return MAPPER_ERROR;
    }


    *pointer = mmap (NULL, blockSize, PROT_READ | PROT_WRITE, MAP_SHARED, memoryFileDescriptor, physicalAddress);
    if (*pointer == MAP_FAILED) {
        close (memoryFileDescriptor);
        return MAPPER_ERROR;
    }

    close (memoryFileDescriptor);

    return MAPPER_SUCCESS;

}

MAPPER_STATUS unmapBaseRegister (void *pointer, const size_t blockSize) {

    if (pointer == NULL || blockSize < 1) {
        return MAPPER_ERROR;
    }

    const int memoryUnmap = munmap (pointer, blockSize);

    if (memoryUnmap < 0) {
        return MAPPER_ERROR;
    }

    return MAPPER_SUCCESS;

}