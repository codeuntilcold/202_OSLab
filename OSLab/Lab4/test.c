#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int glo_init_data = 99;
int glo_noninit_data;

void print_func() {
	int local_data = 9;
	printf("Process ID = %d\n", getpid());
	printf("Addresses of the process:\n");
	printf("1. glo_init_Data = \t%p\n", &glo_init_data);
	printf("2. glo_noninit_data = \t%p\n", &glo_noninit_data);
	printf("3. print_func() = \t%p\n", &print_func);
	printf("4. local_data = \t%p\n", &local_data);
}

void heap_test() {
	const size_t MB = 1024 * 1024;
	size_t maxMB = 0;
	void* ptr = NULL;
	int i = 0;
	do {
		if (ptr) {
			printf("Bytes of memory checked: %zi\n", maxMB);
			memset(ptr, 0, maxMB);
		}
		maxMB += MB;
		ptr = malloc(maxMB);
		i++;
	}
	while (ptr);
}

void* simple_malloc(size_t size) {
	void* p;
	p = sbrk(0);
	if (sbrk(size) == (void*)-1)
		return NULL;
	return p;
}

int main(int argc, char** argv) {
	// print_func();
	// heap_test();
	printf("%p\n", simple_malloc(0));
	return 0;
}

