#include "libmx.h"

int mx_atoi(const char *str) {
    long long result = 0;
    while (*str == ' ') str++;
    int sign = str[0] == '-' ? -1 : 1;
    if (str[0] == '+') str++;
    for (int i = sign < 0; mx_isdigit(str[i]); i++) {
        if (sign > 0) {
            if (result + (str[i] - '0') < 0) return -1;
            result += str[i] - '0';
        }
        else {
            if (result - (str[i] - '0') > 0) return 0;
            result -= str[i] - '0';
        }
        if (mx_isdigit(str[i + 1])) result *= 10;
    }
    return (int)result;
}
