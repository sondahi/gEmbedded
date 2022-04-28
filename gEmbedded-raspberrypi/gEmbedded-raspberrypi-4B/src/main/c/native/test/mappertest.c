#include <stdio.h>
#include <CUnit/Basic.h>

#include "mapper.h"

static void* pointer;
static const char* fileName = "/dev/mem";
static const size_t blockSize = 0xF4;
static const off_t physicalAddress = 0xFE200000;


int init_suite(void) {
    printf("init");
    return 0;
}

int clean_suite(void) {
    printf("destroy");
    return 0;
}

void testMapBaseRegister() {
    printf("map");
    MapperStatus status = mapBaseRegister(&pointer, fileName, blockSize, physicalAddress);
    if (MAPPER_SUCCESS /*check result*/) {
        CU_ASSERT(status);
    }
}

void testUnmapBaseRegister() {
    printf("unmap");
    MapperStatus status = unmapBaseRegister(pointer, blockSize);
    if (MAPPER_SUCCESS /*check result*/) {
        CU_ASSERT(status);
    }
}
