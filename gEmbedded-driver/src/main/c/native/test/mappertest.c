#include <CUnit/Basic.h>

#include "mapper.h"

static void *pointer;
static const char *fileName = "/dev/mem";
static const size_t blockSize = 0xF4; // GPIO
static const off_t physicalAddress = 0xFE200000; // GPIO

void testFailMapWhenPhysicalAddressIsNotValid (void) {
    off_t inValidPhysicalAddress = 0x0;
    MAPPER_STATUS status = mapBaseRegister (inValidPhysicalAddress, blockSize, fileName, &pointer);
    CU_ASSERT_NOT_EQUAL(status, MAPPER_SUCCESS)
    CU_ASSERT_EQUAL(status, MAPPER_PHYSICAL_ADDRESS_ERROR)
}

void testFailMapWhenBlockSizeIsNotValid (void) {
    size_t inValidBlockSize = 0;
    MAPPER_STATUS status = mapBaseRegister (physicalAddress, inValidBlockSize, fileName, &pointer);
    CU_ASSERT_NOT_EQUAL(status, MAPPER_SUCCESS)
    CU_ASSERT_EQUAL(status, MAPPER_BLOCK_SIZE_ERROR)

    inValidBlockSize = 4097;
    status = mapBaseRegister (physicalAddress, inValidBlockSize, fileName, &pointer);
    CU_ASSERT_NOT_EQUAL(status, MAPPER_SUCCESS)
    CU_ASSERT_EQUAL(status, MAPPER_BLOCK_SIZE_ERROR)
}

void testFailMapWhenFileNameIsNotValid (void) {
    char *invalidNullFileName = NULL;
    MAPPER_STATUS status = mapBaseRegister (physicalAddress, blockSize, invalidNullFileName, &pointer);
    CU_ASSERT_NOT_EQUAL(status, MAPPER_SUCCESS)
    CU_ASSERT_EQUAL(status, MAPPER_FILE_NAME_ERROR)

    char *inValidFileName = "/dev/invalidFile";
    status = mapBaseRegister (physicalAddress, blockSize, inValidFileName, &pointer);
    CU_ASSERT_NOT_EQUAL(status, MAPPER_SUCCESS)
    CU_ASSERT_EQUAL(status, MAPPER_FILE_OPEN_ERROR)
}

void testSuccessMapBaseRegister (void) {
    MAPPER_STATUS status = mapBaseRegister (physicalAddress, blockSize, fileName, &pointer);
    CU_ASSERT_EQUAL(status, MAPPER_SUCCESS)
}

void testFailUnmapWhenBlockSizeIsNotValid (void) {
    size_t inValidBlockSize = 0;
    MAPPER_STATUS status = unmapBaseRegister (inValidBlockSize, pointer);
    CU_ASSERT_NOT_EQUAL(status, MAPPER_SUCCESS)
    CU_ASSERT_EQUAL(status, MAPPER_BLOCK_SIZE_ERROR)

    inValidBlockSize = 4097;
    status = unmapBaseRegister (inValidBlockSize, pointer);
    CU_ASSERT_NOT_EQUAL(status, MAPPER_SUCCESS)
    CU_ASSERT_EQUAL(status, MAPPER_BLOCK_SIZE_ERROR)
}

void testFailUnmapWhenPointerIsNotValid (void) {
    void *invalidPointer = NULL;
    MAPPER_STATUS status = unmapBaseRegister (blockSize, invalidPointer);
    CU_ASSERT_NOT_EQUAL(status, MAPPER_SUCCESS)
    CU_ASSERT_EQUAL(status, MAPPER_POINTER_ERROR)
}

void testSuccessUnmapBaseRegister (void) {
    MAPPER_STATUS status = unmapBaseRegister (blockSize, pointer);
    CU_ASSERT_EQUAL(status, MAPPER_SUCCESS)
}
