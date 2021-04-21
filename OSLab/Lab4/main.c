#include "ex1.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main() 
{   
    // printf("size of void* = %ld\n", sizeof(void*));
    unsigned int size = 4;
    unsigned int align = 4;
    int* array = (int*)aligned_malloc(size, align);
    printf("address of array = %lu\n", array);
    memset(array, 0, size);
    for (int i = 0; i < size / sizeof(int); i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    aligned_free(array);
}