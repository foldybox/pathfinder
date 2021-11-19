// mx_create_node.c

#include "libmx.h"

unsigned long mx_hex_to_nbr(const char *hex) {
    int length = 0;
    unsigned long num = 0;
    unsigned long start = 1;

    if (hex != NULL) {
        while (hex[length]) {
            length++;
        }
    }
    else return 0;

    for (int i = 0; i <= length; i++) {
        if (mx_isdigit(hex[length - i])) {
            num = num + (hex[length - i] - 48) * start;
            start *= 16;
        } 
        else if (mx_isalpha(hex[length - i])) {
            if (hex[length - i] >= 'A' && hex[length - i] <= 'F'){
                num = num + (hex[length - i] - 55) * start;
                start *= 16;
            } 
            else if (hex[length - i] >= 'a' && hex[length - i] <= 'f'){
                num = num + (hex[length - i] - 87) * start;
                start *= 16;
            }
        }
    }

    return num;
}
