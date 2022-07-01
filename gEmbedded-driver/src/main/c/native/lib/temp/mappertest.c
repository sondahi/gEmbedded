#include <CUnit/Basic.h>
#include "mapper.h"
#include "mappertest.h"
#include "common.h"

static void *pointer;

#define MEMORY_FILE_NAME    ("/dev/mem")
#define GPIO_BASE_ADDRESS   (PERIPHERAL_BASE_ADDRESS + 0x200000)
#define GPIO_BLOCK_SIZE     (0xF4)

void testMapBaseRegister (void) {
    MAPPER_STATUS status;

    status = mapBaseRegister (NULL, GPIO_BLOCK_SIZE, GPIO_BASE_ADDRESS, &pointer);
    CU_ASSERT_EQUAL(status, MAPPER_ERROR)

    status = mapBaseRegister (MEMORY_FILE_NAME, 0, GPIO_BASE_ADDRESS, &pointer);
    CU_ASSERT_EQUAL(status, MAPPER_ERROR)

    status = mapBaseRegister (MEMORY_FILE_NAME, GPIO_BLOCK_SIZE, -2, &pointer);
    CU_ASSERT_EQUAL(status, MAPPER_ERROR)

    status = mapBaseRegister ("/dev/invalidFile", GPIO_BLOCK_SIZE, GPIO_BASE_ADDRESS, &pointer);
    CU_ASSERT_EQUAL(status, MAPPER_ERROR)

    status = mapBaseRegister (MEMORY_FILE_NAME, GPIO_BLOCK_SIZE, GPIO_BASE_ADDRESS, &pointer);
    CU_ASSERT_EQUAL(status, MAPPER_SUCCESS)
}

void testUnmapBaseRegister (void) {
    MAPPER_STATUS status;

    status = unmapBaseRegister (NULL, GPIO_BLOCK_SIZE);
    CU_ASSERT_EQUAL(status, MAPPER_ERROR)

    status = unmapBaseRegister (pointer, 0);
    CU_ASSERT_EQUAL(status, MAPPER_ERROR)

    status = unmapBaseRegister (pointer, GPIO_BLOCK_SIZE);
    CU_ASSERT_EQUAL(status, MAPPER_SUCCESS)
}
