// mx_push_back.c

#include "libmx.h"

void mx_push_back(t_list **list, void *data) {
    if(!*list) {
        *list = mx_create_node(data);
        return;
    }

    t_list *buff = *list;
    while (buff->next) {
        buff = buff->next;
    }

    buff->next = mx_create_node(data);
}
