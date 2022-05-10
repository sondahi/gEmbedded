#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include "mapper.h"

MAPPER_STATUS
mapBaseRegister (const char *fileName, const size_t blockSize, const off_t physicalAddress, void **pointer) {

    const int memoryFileDescriptor = open (fileName, O_RDWR | O_SYNC);

    if (memoryFileDescriptor < 0) {
        close (memoryFileDescriptor);
        return MAPPER_FILE_OPEN_ERROR;
    }

    *pointer = mmap (NULL, blockSize, PROT_READ | PROT_WRITE, MAP_SHARED, memoryFileDescriptor, physicalAddress);
    if (*pointer == MAP_FAILED) {
        close (memoryFileDescriptor);
        return MAPPER_MEMORY_MAP_ERROR;
    }

    close (memoryFileDescriptor);

    return MAPPER_SUCCESS;

}

MAPPER_STATUS unmapBaseRegister (void *pointer, const size_t blockSize) {

    const int memoryUnmap = munmap (pointer, blockSize);

    if (memoryUnmap < 0) {
        return MAPPER_MEMORY_UNMAP_ERROR;
    }

    return MAPPER_SUCCESS;

}