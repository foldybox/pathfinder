// mx_binary_search.c

#include "libmx.h"

int mx_binary_search(char **arr, int size, const char *s, int *count){
    int bottom = 0;
    int top = size - 1;
    int center;

    while (bottom <= top) {
        *count = *count + 1;
        center = (bottom + top) / 2;

        if (mx_strcmp(arr[center], s) > 0) top = center - 1;
        else if (mx_strcmp(arr[center], s) < 0) bottom = center + 1;
        else return center;
    }

    *count = 0;
    return -1;
}
