#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include "mapper.h"

#define INVALID_PHYSICAL_ADDRESS    (0x0)
#define MIN_BLOCK_SIZE              (1)
#define MAX_BLOCK_SIZE              (4096)

MAPPER_STATUS mapBaseRegister (const off_t physicalAddress, const size_t blockSize, const char *fileName, void **pointer) {

    if (physicalAddress == INVALID_PHYSICAL_ADDRESS) {
        return MAPPER_PHYSICAL_ADDRESS_ERROR;
    }

    if (blockSize < MIN_BLOCK_SIZE || blockSize > MAX_BLOCK_SIZE) {
        return MAPPER_BLOCK_SIZE_ERROR;
    }

    if (fileName == NULL) {
        return MAPPER_FILE_NAME_ERROR;
    }

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

MAPPER_STATUS unmapBaseRegister (const size_t blockSize, void *pointer) {

    if (blockSize < MIN_BLOCK_SIZE || blockSize > MAX_BLOCK_SIZE) {
        return MAPPER_BLOCK_SIZE_ERROR;
    }

    if (pointer == NULL) {
        return MAPPER_POINTER_ERROR;
    }

    const int memoryUnmap = munmap (pointer, blockSize);

    if (memoryUnmap < 0) {
        return MAPPER_MEMORY_UNMAP_ERROR;
    }

    return MAPPER_SUCCESS;

}

MAPPER_STATUS mapperStatusCheck(const char *message, MAPPER_STATUS status, char *messageToReturn){

    switch (status) {
        case MAPPER_PHYSICAL_ADDRESS_ERROR: {
            sprintf(messageToReturn,"Invalid memory map physical address : %s", message);
            return MAPPER_EXCEPTION_OCCURRED;
        }
        case MAPPER_BLOCK_SIZE_ERROR: {
            sprintf(messageToReturn,"Invalid memory block size : %s", message);
            return MAPPER_EXCEPTION_OCCURRED;
        }
        case MAPPER_FILE_NAME_ERROR: {
            sprintf(messageToReturn,"Invalid memory file name : %s", message);
            return MAPPER_EXCEPTION_OCCURRED;
        }
        case MAPPER_FILE_OPEN_ERROR: {
            sprintf(messageToReturn,"Memory file could not be opened : %s", message);
            return MAPPER_EXCEPTION_OCCURRED;
        }
        case MAPPER_MEMORY_MAP_ERROR: {
            sprintf(messageToReturn,"Memory mapping failed : %s", message);
            return MAPPER_EXCEPTION_OCCURRED;
        }
        case MAPPER_MEMORY_UNMAP_ERROR: {
            sprintf(messageToReturn,"Memory unmapping failed : %s", message);
            return MAPPER_EXCEPTION_OCCURRED;
        }
        default: {
            return MAPPER_SUCCESS;
        }
    }

}