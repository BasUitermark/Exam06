#include <stdio.h>
#include <stdlib.h>
#include "power_of_2.c"

int pow_of_2(unsigned int n);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    unsigned int n = atoi(argv[1]);
    printf("%d\n", pow_of_2(n));

    return 0;
}