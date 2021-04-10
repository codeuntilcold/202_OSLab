#include "readline.h"

int read_line(char* str)
{
	char c;
	int count = 0;
	for (int i = 0; i < 100; i++) str[i] = '\0';
	while (1) {
		scanf("%c", &c);
		if (c == '\n' || count == 99) return count;
		if (c == EOF || c == '\0') return -1;
		str[count++] = c;
	}
}
