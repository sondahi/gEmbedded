#include <CUnit/Basic.h>

#include "mapper.h"

static void *pointer;
static const char *fileName = "/dev/mem";
static const size_t blockSize = 0xF4; // GPIO
static const off_t physicalAddress = 0xFE200000; // GPIO

void testFailMapWhenPhysicalAddressIsNotValid(void) {
    off_t inValidPhysicalAddress = 0;
    MapperStatus status = mapBaseRegister(inValidPhysicalAddress, blockSize, fileName, &pointer);
    CU_ASSERT_NOT_EQUAL(MAPPER_SUCCESS, status)
    CU_ASSERT_EQUAL(MAPPER_PHYSICAL_ADDRESS_ERROR, status)
}
void testFailMapWhenBlockSizeIsNotValid(void) {
    size_t inValidBlockSize = 0;
    MapperStatus status = mapBaseRegister(physicalAddress, inValidBlockSize, fileName, &pointer);
    CU_ASSERT_NOT_EQUAL(MAPPER_SUCCESS, status)
    CU_ASSERT_EQUAL(MAPPER_BLOCK_SIZE_ERROR, status)

    inValidBlockSize = 4097;
    status = mapBaseRegister(physicalAddress, inValidBlockSize, fileName, &pointer);
    CU_ASSERT_NOT_EQUAL(MAPPER_SUCCESS, status)
    CU_ASSERT_EQUAL(MAPPER_BLOCK_SIZE_ERROR, status)
}

void testFailMapWhenFileNameIsNotValid(void) {
    const char *inValidFileName = "/dev/invalidFile";
    MapperStatus status = mapBaseRegister(physicalAddress, blockSize, inValidFileName, &pointer);
    CU_ASSERT_NOT_EQUAL(MAPPER_SUCCESS, status)
    CU_ASSERT_EQUAL(MAPPER_FILE_OPEN_ERROR, status)
}

void testSuccessMapBaseRegister(void) {
    MapperStatus status = mapBaseRegister(physicalAddress, blockSize, fileName, &pointer);
    CU_ASSERT_EQUAL(MAPPER_SUCCESS, status)
}

void testFailUnmapWhenBlockSizeIsNotValid(void) {
    size_t inValidBlockSize = 0;
    MapperStatus status = unmapBaseRegister(inValidBlockSize, pointer);
    CU_ASSERT_NOT_EQUAL(MAPPER_SUCCESS, status)
    CU_ASSERT_EQUAL(MAPPER_BLOCK_SIZE_ERROR, status)

    inValidBlockSize = 4097;
    status = unmapBaseRegister(inValidBlockSize, pointer);
    CU_ASSERT_NOT_EQUAL(MAPPER_SUCCESS, status)
    CU_ASSERT_EQUAL(MAPPER_BLOCK_SIZE_ERROR, status)
}

void testFailUnmapWhenPointerIsNotValid(void) {
    static void *invalidPointer = NULL;
    MapperStatus status = unmapBaseRegister(blockSize, invalidPointer);
    CU_ASSERT_NOT_EQUAL(MAPPER_SUCCESS, status)
    CU_ASSERT_EQUAL(MAPPER_POINTER_ERROR, status)
}

void testSuccessUnmapBaseRegister(void) {
    MapperStatus status = unmapBaseRegister(blockSize, pointer);
    CU_ASSERT_EQUAL(MAPPER_SUCCESS, status)
}
