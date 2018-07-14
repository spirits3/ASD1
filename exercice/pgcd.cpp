#include <stdlib.h>

int pgcd(int a, int b) {
    return (b)? pgcd(b,a%b): a;
}

