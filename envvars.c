#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "header.h"

/* Function to concatenate two strings */
char* concatenate_strings(const char* str1, const char* str2) 
{
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    char* result = malloc(len1 + len2 + 1);
    if (result == NULL) 
    {
        fprintf(stderr, "Error: Failed to allocate memory for concatenation\n");
        exit(EXIT_FAILURE);
    }
    strcpy(result, str1);
    strcat(result, str2);
    return (result);
}

int main() 
{
    /* Retrieve data from a source */
    char* data = retrieve_data();

    /* Print the retrieved data */
    printf("Retrieved data: %s\n", data);

    /* Free the allocated memory */
    free(data);

    return (0);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * get_environment - Retrieves a copy of the "environ" array.
 * @info: A structure holding potential arguments, maintaining a consistent
 *         function prototype.
 *
 * Return: Returns a copy of the "environ" array.
 */
char **get_environment(info_t *info)
{
    if (!info->env_data || info->env_data_changed)
    {
        info->env_data = convert_list_to_strings(info->env_list);
        info->env_data_changed = 0;
    }
    return (info->env_data);
}

/**
 * remove_environment_variable - Deletes an environment variable.
 * @info: A structure holding potential arguments, ensuring a consistent
 *        function prototype.
 * @remenv: The environment variable's name to be removed.
 *
 * Return: Returns 1 upon successful deletion, 0 otherwise.
 */
int remove_environment_variable(info_t *info, char *remenv)
{
    list_t *node = info->env_list;
    size_t index = 0;
    char *start;

    if (!node || !remenv)
        return (0);

    while (node)
    {
        start = starts_with(node->str, remenv);
        if (start && *start == '=')
        {
            info->env_data_changed = remove_element_at_position(&(info->env_list), index);
            index = 0;
            node = info->env_list;
            continue;
        }
        node = node->next;
        index++;
    }
    return (info->env_data_changed);
}

/**
 * set_environment_variable - Create a new environment variable or modify an existing one.
 * @info: A structure holding potential arguments to maintain a consistent
 *        function prototype.
 * @envvar: The name of the environment variable.
 * @envval: The value of the environment variable.
 *
 * Return: Always returns 0.
 */
int set_environment_variable(info_t *info, char *envvar, char *envval)
{
    char *buf = NULL;
    list_t *node;
    char *start;

    if (!envvar || !envval)
        return (0);

    buf = malloc(strlen(envvar) + strlen(envval) + 2);
    if (!buf)
        return (1);

    strcpy(buf, envvar);
    strcat(buf, "=");
    strcat(buf, envval);

    node = info->env_list;
    while (node)
    {
        start = starts_with(node->str, envvar);
        if (start && *start == '=')
        {
            free(node->str);
            node->str = buf;
            info->env_data_changed = 1;
            return (0);
        }
        node = node->next;
    }

    insert_node_end(&(info->env_list), buf, 0);
    free(buf);
    info->env_data_changed = 1;
    return (0);
}
