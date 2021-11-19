// mx_push_front.c

#include "libmx.h"

void mx_push_front(t_list **list, void *data) {
    if (!*list) {
        *list = mx_create_node(data);
        return;
    }

    t_list *buff = mx_create_node(data);
    buff->next = *list;
    *list = buff;
}
