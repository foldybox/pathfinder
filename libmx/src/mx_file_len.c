// mx_file_len.c

#include "libmx.h"

int mx_file_len(const char *file) {
	int file_d = open(file, O_RDONLY);
    int len = 0;
    char buffer;

	for(int size = read(file_d, &buffer, 1); size > 0; size = read(file_d, &buffer, 1)) {
        len++;
    }
		
    close(file_d);
    return len;
}
