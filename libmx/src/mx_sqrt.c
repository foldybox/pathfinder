// mx_sqrt.c

#include "libmx.h"

int mx_sqrt(int x){
    if (x < 0) return 0;
    else {
        float res = x / 2;
        float buf = 0;
        for (int i = 0; res != buf; ++i) {
            buf = res;
            res = (x / buf + buf) / 2;
        }

        if ((int)(res * 10) % 10 == 0) {
            return (int) res;
        }
        else {
            return 0;
        }
    }
}
