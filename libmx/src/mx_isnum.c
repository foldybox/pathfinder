#include "libmx.h"

bool mx_isnum(const char *s)
{
    if (*s == '-') s++;
    while (*s != '\0')
    {
        if (!mx_isdigit(*s)) return false;
        s++;
    }
    return true;
}
