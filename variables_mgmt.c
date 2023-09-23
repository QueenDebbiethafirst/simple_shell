#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* Function prototypes */
void display_list_items_str(list_t *list);
char *starts_with(const char *str, const char *prefix); // Changed return type to char*
void output_error(const char *error_message);
void insert_node_end(list_t **list, const char *str, int value);

/* Declare Info_env_data at the beginning of the file or in a header file. */
list_t *Info_env_data = NULL;

void fill_env_list(void) {
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++) {
        insert_node_end(&node, environ[i], 0);
    }

    Info_env_data = node;
}

char *retrieve_env(const char *env_var_name) { // Changed return type to char*
    list_t *node = Info_env_data;
    char *value;

    while (node) {
        value = starts_with(node->str, env_var_name);
        if (value && *value)
            return value;
        node = node->next;
    }

    return NULL;
}

int custom_set_environment(info_t *info) {
    if (info->argc != 3) {
        output_error("Incorrect number of arguments\n");
        return 1;
    }

    if (setenv(info->argv[1], info->argv[2], 1) != 0) {
        output_error("Failed to set environment variable\n");
        return 1;
    }

    return 0;
}

int delete_env_variable(info_t *info) {
    int i;

    if (info->argc == 1) {
        output_error("Too few arguments.\n");
        return 1;
    }

    for (i = 1; i < info->argc; i++) {
        if (unsetenv(info->argv[i]) != 0) {
            output_error("Failed to unset environment variable\n");
            return 1;
        }
    }

    return 0;
}

int main() {
    /* Main program logic */
    return 0;
}

int user_environment(info_t *info) {
    display_list_items_str(Info_env_data);
    return 0;
}
