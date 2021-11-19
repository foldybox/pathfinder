// mx_pow.c

#include "libmx.h"

double mx_pow(double n, unsigned int pow) {
    double res = n;

    if (pow  == 0) {
        res = 1;
    }
    else {
        for (unsigned int i = 1; i < pow; ++i) {
            res *= n;
        }
    }

    return res;
}
