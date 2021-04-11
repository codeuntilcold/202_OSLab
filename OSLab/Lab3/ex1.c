#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int readline(char* num, FILE* fp) {
    int i = 0;
    while (1) {
        char temp = fgetc(fp);
        if (temp == '\n' || temp == EOF) {
            num[i] = '\0';
            return (temp == '\n') ? i : EOF;
        }
        num[i++] = temp;
        if (i == 79) {
            num[i] = '\0';
            return i;
        }
    }
    return 0;
}

int is_div_3(char* num) {
    int len = strlen(num);
    if (len < 1) return 0;
    int sum = 0;
    for (int i = 0; i < len; i++) {
        sum += num[i] - '0';
    }
    return (sum % 3 == 0) ? 1 : 0;
}

int is_div_7(char* num) {
    // Ans = (Ans * 3 + <next digit>) % 7
    int len = strlen(num);
    if (len < 1) return 0;
    int rem = (num[0] - '0') % 7;
    for (int i = 1; i < len; i++) {
        rem = (rem * 3 + num[i] - '0') % 7;
    }
    return (rem == 0) ? 1 : 0;
}

int is_div_11(char* num) {
    int len = strlen(num);
    if (len < 1) return 0;
    int odd = 0, even = 0;
    for (int i = 0; i < len; i++) {
        if (i % 2 == 0)
            even += num[i] - '0';
        else
            odd += num[i] - '0';
    }
    return ((even - odd) % 11 == 0) ? 1 : 0;
}

int main(int argc, char** argv)
{
    // Requirements: read non-negative numbers from "numbers.txt"
    // and print out the number of numbers divisible by 3, 7, 11
    // Number is less than 10^79

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("Can't open file");
        exit(1);
    }

    char number[80];
    int count = 0;
    pid_t child_1 = fork();

    if (child_1 < 0) 
    {
        perror("Fork error");
    }
    else if (child_1 == 0) 
    {
        pid_t child_2 = fork();
        if (child_2 < 0) {
            perror("Fork error");
            exit(1);
        }
        else if (child_2 == 0) {
            // In child_2
            while (1) {
            int len = readline(number, fp);
            if (is_div_3(number)) {
                count++;
            }
            if (len == EOF)
                break;
        }
        printf("%d\n", count);
        }
        else {
            // In child_1
            wait(NULL);
            rewind(fp);
            while (1) {
                int len = readline(number, fp);
                if (is_div_7(number)) {
                    count++;
                }
                if (len == EOF)
                    break;
            }
            printf("%d\n", count);            
        }
    }
    else 
    {
        // In main proc
        wait(NULL);
        rewind(fp);
        while (1) {
            int len = readline(number, fp);
            if (is_div_11(number)) {
                count++;
            }
            if (len == EOF)
                break;
        }
        printf("%d\n", count);
    }

    // do {
    //     fgets(number, 255, fp);
    //     printf("%s\n", number);
    //     sleep(1);
    // }
    // while (number);


    fclose(fp);
}