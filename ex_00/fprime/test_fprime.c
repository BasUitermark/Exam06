#include <stdio.h>
#include <stdlib.h>
#include "fprime.c"

void fprime(int n);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    fprime(n);

    return 0;
}
