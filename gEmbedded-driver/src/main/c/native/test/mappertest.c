#include <CUnit/Basic.h>
#include "mappertest.h"

static void *pointer;
static const char *fileName = "/dev/mem";
static const size_t blockSize = 0xF4; // GPIO
static const off_t physicalAddress = 0xFE200000; // GPIO

void testMapBaseRegister (void) {
    char *inValidFileName;
    MAPPER_STATUS status;

    inValidFileName = NULL;
    status = mapBaseRegister (inValidFileName, blockSize, physicalAddress, &pointer);
    CU_ASSERT_NOT_EQUAL(status, MAPPER_SUCCESS)
    CU_ASSERT_EQUAL(status, MAPPER_FILE_OPEN_ERROR)

    inValidFileName = "/dev/invalidFile";
    status = mapBaseRegister (inValidFileName, blockSize, physicalAddress, &pointer);
    CU_ASSERT_NOT_EQUAL(status, MAPPER_SUCCESS)
    CU_ASSERT_EQUAL(status, MAPPER_FILE_OPEN_ERROR)

    size_t invalidBlockSize = 0;
    status = mapBaseRegister (fileName, invalidBlockSize, physicalAddress, &pointer);
    CU_ASSERT_NOT_EQUAL(status, MAPPER_SUCCESS)
    CU_ASSERT_EQUAL(status, MAPPER_MEMORY_MAP_ERROR)

    off_t inValidPhysicalAddress = -1;
    status = mapBaseRegister (fileName, blockSize, inValidPhysicalAddress, &pointer);
    CU_ASSERT_NOT_EQUAL(status, MAPPER_SUCCESS)
    CU_ASSERT_EQUAL(status, MAPPER_MEMORY_MAP_ERROR)

    status = mapBaseRegister (fileName, blockSize, physicalAddress, &pointer);
    CU_ASSERT_EQUAL_FATAL(status, MAPPER_SUCCESS)
}

void testUnmapBaseRegister (void) {
    void *invalidPointer = (void *) -1;
    MAPPER_STATUS status = unmapBaseRegister (invalidPointer, blockSize);
    CU_ASSERT_NOT_EQUAL(status, MAPPER_SUCCESS)
    CU_ASSERT_EQUAL(status, MAPPER_MEMORY_UNMAP_ERROR)

    status = unmapBaseRegister (pointer, blockSize);
    CU_ASSERT_EQUAL_FATAL(status, MAPPER_SUCCESS)
}
