#ifndef OS_PROJEKAT_MEMORYALLOCATOR_HPP
#define OS_PROJEKAT_MEMORYALLOCATOR_HPP

#include "../lib/hw.h"
extern const void* FREE_MEM_HEAD;
void* memory_alloc(size_t size);
void memory_initialization();
int memory_free(void* ptr);
#endif //OS_PROJEKAT_MEMORYALLOCATOR_HPP