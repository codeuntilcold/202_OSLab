#include <stdio.h>
#include "readline.h"
#include "findsubstr.h"

int main(int argc, char** argv)
{
    char str[100];
    int count;
    int pos;
    while (1) {
        count = read_line((char*)&str);
        // printf("Read: %s\n", str);
        if (count == -1) break;
        if (count != 0) {
            pos = find_sub_string(str, argv[1]);
            if(pos != -1) {
                printf("%s\n", str);
            }
        }
    }
}
