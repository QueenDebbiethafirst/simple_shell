#ifndef LIST_H
#define LIST_H

typedef struct list_t {
    // Define the members of the list structure here
    char *str;
    struct list_t *next;
} list_t;

#endif
