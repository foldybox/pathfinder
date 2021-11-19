// mx_sort_list.c

#include "libmx.h"

t_list *mx_sort_list(t_list *list, bool (*cmp)(void *a, void *b)) {
    if (cmp == NULL || list == NULL) {
        return list;
    }

    t_list *buff = list;
    int counter = 0;
    while (buff) {
        buff = buff->next;
        counter++;
    }

    for (int i = 0; i < counter; i++) {
        buff = list;
        for (int j = 0; j < counter - 1; j++) {
            if (cmp(buff->data, buff->next->data)) {
                void *data = buff->data;
                buff->data = buff->next->data;
                buff->next->data = data;
            }
            buff = buff->next;
        }
    }
    return list;
}
