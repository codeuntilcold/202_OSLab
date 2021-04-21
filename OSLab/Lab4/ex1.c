#include "ex1.h"
#include <unistd.h>
#include <stdlib.h>

int is_multiple_of_2(unsigned int num) {
    if (num < 1) return 0;
    while (num % 2 == 0) {
        num /= 2;
    }
    return (num == 1);
}

void* aligned_malloc(unsigned int size, unsigned int align) {
    /*
        REQ: address of the allocated memory is a multiple of align
        align must be a power of two and > 0
        If size == 0 or can't allocate -> return NULL
    */
    if (!is_multiple_of_2(align) || size < 1) {
        return NULL;
    }
    /* 
        When we call malloc(), we cant be sure that it will
        land on the exact alignment that we want,
        so we ask for 'align - 1' extra to add extra space so 
        we can shift the starting block to the exact position.

        And we ask for another sizeof(void*) to bookkeeping 
        the original allocated block address.
    */
    void* block_start;
    void** align_start;
    unsigned int offset = align - 1 + sizeof(void*);
    if ((block_start = malloc(size + offset)) == NULL) {
        return NULL;
    }
    /* 
        Stackoverflow:
            align_start = (void**)(((size_t)(block_start) + offset) & ~(align - 1));
        Because align is a power of 2, it has the form  0x000000100000000
        so ~(align - 1) will have the form              0x111111100000000
        which mean that this line of code will shift the block_start 
        forward, then backward, until it is aligned.
        But if align is smaller than sizeof(void*), it means that the aligned address
        may not be large enough to store a void* in front of it.
        So we do this :)
    */
    align_start = (void**)((size_t)block_start + sizeof(void*));
    align_start = (void**)((size_t)align_start + align - (size_t)(align_start) % align);
    align_start[-1] = block_start;
    return align_start;
}

void* aligned_free(void* ptr) {
    if (!ptr)
        return NULL;
    free(((void**)ptr)[-1]);
    return NULL;
}
