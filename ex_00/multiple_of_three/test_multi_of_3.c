#include <stdio.h>
#include <stdlib.h>
#include "multiple_of_3.c"

int multi_of_3(unsigned int n);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    unsigned int n = atoi(argv[1]);
    printf("%d\n", multi_of_3(n));

    return 0;
}