#ifndef INFO_H
#define INFO_H

#include <stddef.h>

typedef struct liststr {
    /* Define the fields of your liststr structure here */
    char *data;
    struct liststr *next;
} liststr;

/* Define the original info_t structure */
typedef struct info_t {
    char *arg;
    char **argv;
    char *delimiter_string;
    char chr;
    liststr *history;
    liststr *alias;
    int argc;
    char *input_string;
} info_t;

/* Define the additional info_t structure */
typedef struct info_s {
    list_t *history;
    int hist_count;
    char **argv;
    int input_stream;
    int linecount_flag;
    int histcount;
    int cmd_buf_type;
    char **arg;
    char *fetch_history_file;
    int record_history;
    int open_history;
} info_t;

/* Define the new info_t structure with the function pointer */
typedef struct info_t {
    char *type;
    int (*func)(struct info_t *);
    // ... members ...
} info_t;

#endif /* INFO_H */
