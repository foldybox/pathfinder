// mx_file_to_str.c

#include "libmx.h"

char *mx_file_to_str(const char *file) {
    int count = 0;
    char buf[1];
    int fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        close(fd);
        return NULL;
    }
    while (read(fd, buf, 1) != 0) count++;
    close(fd);
    if (count == 0) return mx_strnew(0);
    fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        close(fd);
        return NULL;
    }
    char *res = mx_strnew(count);
    if (read(fd, res, count) != count) return NULL;
    close(fd);
    return res;
}
