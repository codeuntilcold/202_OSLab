#ifndef _CUSTOM_MALLOC_
#define _CUSTOM_MALLOC_

void* aligned_malloc(unsigned int size, unsigned int align);

void* aligned_free(void* ptr);

#endif