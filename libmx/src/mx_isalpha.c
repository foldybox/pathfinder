// mx_isalpha.c

#include "libmx.h"

bool mx_isalpha(int c){
    if(c >= 65 && c <= 122) {
        return true;
    }
    else {
        return false;
    }
}
