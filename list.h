#ifndef LIST_H
#define LIST_H

#include "list.h"

typedef struct list_t {
    // Define the members of the list structure here
    char *str;
    struct list_t *next;
char *nodestr;
    int histnum;
char *data;
    int whether;
} list_t;

#endif
