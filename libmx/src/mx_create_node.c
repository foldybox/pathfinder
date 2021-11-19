// mx_create_node.c

#include "libmx.h"

t_list *mx_create_node(void *data) {
    t_list *node = malloc(16);
    node->next = NULL;
    node->data = data;

    return node;
}
