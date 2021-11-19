// mx_list_size.c

#include "libmx.h"

int mx_list_size(t_list *list) {
    int counter = 0;

    while(list) {
        list = list -> next;
        counter++;
    }

    return counter;
}
