#include "header.h"
#include <stdio.h> 
#include "list.h"

/**
* check_command - Checks whether a file is an executable command.
* @info: The information struct.
* @filepath: The path to the file.
*
* Return: Returns 1 if the condition is true, and 0 otherwise.
*/
int check_command(info_t *info, char *filepath)
{
    /* Check if filepath is NULL */
    if (filepath == NULL)
    {
        printf("Error: filepath is NULL\n");
        return (0);
    }

    /* Check if file exists*/
    if (access(filepath, F_OK) == -1)
    {
        printf("Error: File does not exist\n");
        return (0);
    }

    /* Check if file is executable */
    if (access(filepath, X_OK) == -1)
    {
        printf("Error: File is not executable\n");
        return (0);
    }

    /* File is an executable command */
    return (1);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

typedef struct 
{
    /* Add necessary fields for info struct */
} info_t;

/**
 * duplicate_characters - Replicates characters.
 * @pstr: The PATH string.
 * @st: The starting index.
 * @sp: The stopping index.
 *
 * Return: Returns a pointer to a new buffer.
 */
char *duplicate_characters(const char *pstr, int st, int sp)
{
    char *buf = malloc((sp - st + 1) * sizeof(char));
    if (buf == NULL) 
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    int k = 0;
    for (int i = st; i < sp; i++) 
    {
        if (pstr[i] != ':') 
        {
            buf[k++] = pstr[i];
        }
    }
    buf[k] = '\0';
    return (buf);
}

/**
 * locate_path - Finds the cmd in the PATH string.
 * @info: The info struct.
 * @pstr: The PATH string.
 * @cmd: The cmd to find.
 *
 * Return: Full path of cmd if found or NULL.
 */
char *locate_path(info_t *info, const char *pstr, const char *cmd)
{
    if (pstr == NULL) 
    {
        fprintf(stderr, "Invalid PATH string\n");
        return (NULL);
    }

    if (cmd == NULL) 
    {
        fprintf(stderr, "Invalid command\n");
        return (NULL);
    }

    if (strlen(cmd) > 2 && strncmp(cmd, "./", 2) == 0) 
    {
        if (check_command(info, cmd)) 
        {
            return (strdup(cmd));
        }
    }

    int i = 0, curr_pos = 0;
    char *path = NULL;

    while (1) 
    {
        if (!pstr[i] || pstr[i] == ':') 
        {
            path = duplicate_characters(pstr, curr_pos, i);
            if (*path == '\0') 
            {
                path = realloc(path, (strlen(cmd) + 1) * sizeof(char));
                if (path == NULL) 
                {
                    fprintf(stderr, "Memory allocation failed\n");
                    exit(EXIT_FAILURE);
                }
                strcpy(path, cmd);
            } else 
            {
                size_t path_len = strlen(path);
                path = realloc(path, (path_len + strlen(cmd) + 2) * sizeof(char));
                if (path == NULL) 
                {
                    fprintf(stderr, "Memory allocation failed\n");
                    exit(EXIT_FAILURE);
                }
                strcat(path, "/");
                strcat(path, cmd);
            }

            if (check_command(info, path)) 
            {
                return (path);
            }

            if (!pstr[i]) 
            {
                break;
            }
            curr_pos = i;
        }
        i++;
    }

    return (NULL);
}
