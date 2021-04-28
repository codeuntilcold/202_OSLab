#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char** argv) 
{
    if (argc != 2) {
        perror("Invalid, must provide number of points");
        exit(1);
    }
    clock_t s = clock();
    srand(time(0));
    int nPoints = atoi(argv[1]);
    int pic = 0;
    float x, y;
    for (int i = 0; i < nPoints; i++) {
        x = (float) rand() / RAND_MAX;
        y = (float) rand() / RAND_MAX;
        if (x * x + y * y <= 1) pic++;
    }
    clock_t e = clock() - s;
    printf("pi = %f\n", (float) 4 * pic / nPoints);
    printf("runtime: %fs\n", (float) e / CLOCKS_PER_SEC);
    /*
    RESULT: Runtime 21-22s with param = 500 000 000
    */
}