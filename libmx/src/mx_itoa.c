// mx_atoi.c

#include "libmx.h"

char *mx_itoa(int num) {
    char *result;
    if (num == INT_MIN) {
        result = (char *)malloc(sizeof(char) * 12);//-2147483648
        result[0] = '-';
        result[1] = '2';
        result[2] = '1';
        result[3] = '4';
        result[4] = '7';
        result[5] = '4';
        result[6] = '8';
        result[7] = '3';
        result[8] = '6';
        result[9] = '4';
        result[10] = '8';
        result[11] = '\0';
        return result;
    }
    if (num == 0) {
        result = (char *)malloc(sizeof(char) * 2);
        result[1] = '\0';
        result[0] = '0';
        return result;
    }
    int is_positive = 1;
    if (num < 0) {
        is_positive = 0;
        num = -num;
    }

    char buff[22];
    int start_index = 0;
    
    while (num != 0)
    {
        buff[start_index] = num % 10 + '0';
        num /= 10;
        start_index++;
    }

    if (is_positive == 0) {
        buff[start_index] = '-';
        start_index++;
    }
    result = (char *)malloc(sizeof(char) * (start_index + 1));
    result[start_index] = '\0';
    for (int i = start_index - 1; i >= 0; i--) {
        result[start_index - i - 1] = buff[i];
    }
    
    return result;
}
