#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "list.h"

/**
 * fetch_history_file - Retrieves the history file.
 * @info: Parameter structure.
 *
 * Return: Returns an allocated string containing the history file.
 */
char *fetch_history_file(info_t *info)
{
    char *data, *directory;
    directory = retrieve_env(info, "HOME=");
    if (!directory)
        return (NULL);
    data = malloc(sizeof(char) * (strlen(directory) + strlen(HIST_FILE) + 2));
    if (!data)
    {
        free(directory);
        return (NULL);
    }
    strcpy(data, directory);
    strcat(data, "/");
    strcat(data, HIST_FILE);
    free(directory);
    return (data);
}

/**
 * record_history - Generates a new file or adds content to an existing file.
 * @info: The parameter structure.
 *
 * Return: Returns 1 upon success, otherwise -1.
 */
int record_history(info_t *info)
{
    int file_descriptor;
    char *file_name = fetch_history_file(info);
    list_t *current_node = info->history;
    if (!file_name)
        return (-1);
    file_descriptor = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    free(file_name);
    if (file_descriptor == -1)
        return (-1);
    while (current_node)
    {
        print_fd(current_node->str, file_descriptor);
        write_fd('\n', file_descriptor);
        current_node = current_node->next;
    }
    write_fd(CLEAR_BUFFER, file_descriptor);
    close(file_descriptor);
    return (1);
}

/**
 * open_history - Reads history from a file.
 * @info: The parameter structure.
 *
 * Return: Returns histcount if successful; otherwise, returns 0.
 */
int open_history(info_t *info)
{
    int line_count = 0;
    ssize_t file_descriptor, read_length;
    char *file_name = fetch_history_file(info);
    char buffer[1024];
    if (!file_name)
        return (0);
    file_descriptor = open(file_name, O_RDONLY);
    free(file_name);
    if (file_descriptor == -1)
        return (0);
    while ((read_length = read(file_descriptor, buffer, sizeof(buffer))) > 0)
    {
        for (int i = 0; i < read_length; i++)
        {
            if (buffer[i] == '\n')
                line_count++;
        }
    }
    close(file_descriptor);
    return (line_count);
}

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define HIST_MAX 4096

typedef struct list_s {
    char *data;
    int num;
    struct list_s *next;
} list_t;

typedef struct info_s {
    list_t *history;
    int hist_count;
} info_t;

int create_history_list(info_t *info, char *data, int line_count);
int update_history_numbers(info_t *info);

/**
 * fetch_history_file - Fetches the history file name.
 * @info: A structure holding possible arguments, maintaining consistency.
 *
 * Return: The history file name.
 */
char *fetch_history_file(info_t *info)
{
    /*Implementation not provided*/
    return NULL;
}

/**
 * remove_element_at_position - Removes an element at a given position in the linked list.
 * @head: A pointer to the head of the linked list.
 * @position: The position of the element to be removed.
 */
void remove_element_at_position(list_t **head, int position)
{
    /*Implementation not provided*/
}

/**
 * insert_node_end - Inserts a node at the end of the linked list.
 * @head: A pointer to the head of the linked list.
 * @data: The data to be inserted.
 * @line_count: The line count associated with the data.
 */
void insert_node_end(list_t **head, char *data, int line_count)
{
    /*Implementation not provided*/
}

/**
 * fetch_history_file - Fetches the history file name.
 * @info: A structure holding possible arguments, maintaining consistency.
 *
 * Return: The history file name.
 */
char *fetch_history_file(info_t *info)
{
    /* Implementation not provided*/
    return (NULL);
}

/**
 * read_history - Reads the history file and updates the history linked list.
 * @info: A structure holding possible arguments, maintaining consistency.
 *
 * Return: The updated hist_count value.
 */
int read_history(info_t *info)
{
    struct stat st;
    char *data = NULL, *file_name = fetch_history_file(info);
    int file_descriptor, file_size, read_length, line_count = 0, last = 0, i;

    if (!file_name)
        return (0);

    file_descriptor = open(file_name, O_RDONLY);
    free(file_name);

    if (file_descriptor == -1)
        return (0);

    if (fstat(file_descriptor, &st) == -1) 
    {
        close(file_descriptor);
        return (0);
    }

    file_size = st.st_size;

    if (file_size < 2) 
    {
        close(file_descriptor);
        return (0);
    }

    data = malloc(sizeof(char) * (file_size + 1));
    if (!data) 
    {
        close(file_descriptor);
        return (0);
    }

    read_length = read(file_descriptor, data, file_size);
    close(file_descriptor);

    if (read_length <= 0) 
    {
        free(data);
        return 0;
    }

    data[file_size] = '\0';

    for (i = 0; i < file_size; i++) 
    {
        if (data[i] == '\n') 
        {
            data[i] = '\0';
            create_history_list(info, data + last, line_count++);
            last = i + 1;
        }
    }

    if (last != i)
        create_history_list(info, data + last, line_count++);

    free(data);

    info->hist_count = line_count;

    while (info->hist_count >= HIST_MAX)
        remove_element_at_position(&(info->history), 0);

    update_history_numbers(info);

    return (info->hist_count);
}

/**
 * create_history_list - Appends an entry to a linked list for history tracking.
 * @info: A structure holding possible arguments, maintaining consistency.
 * @data: The data.
 * @line_count: The count of history lines, hist_count.
 *
 * Return: Always returns 0.
 */
int create_history_list(info_t *info, char *data, int line_count)
{
    list_t *current_node = NULL;

    if (info->history)
        current_node = info->history;

    insert_node_end(&current_node, data, line_count);

    if (!info->history)
        info->history = current_node;

    return (0);
}

/**
 * update_history_numbers - Updates the numbering of the history linked list following modifications.
 * @info: A structure containing possible arguments, utilized for maintaining consistency.
 *
 * Return: The updated hist_count value.
 */
int update_history_numbers(info_t *info)
{
    list_t *current_node = info->history;
    int i = 0;

    while (current_node) 
    {
        current_node->num = i++;
        current_node = current_node->next;
    }

    return (info->hist_count = i);
}
