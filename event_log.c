#include "header.h"
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
data = malloc(sizeof(char) * (_strlen(directory) + _strlen(HIST_FILE) + 2));
if (!data)
{
free(directory);
return (NULL);
}
data[0] = 0;
_strcpy(data, directory);
_strcat(data, "/");
_strcat(data, HIST_FILE);
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
ssize_t file_descriptor;
char *file_name = fetch_history_file(info);
list_t *current_node = NULL;
if (!file_name)
return (-1);
file_descriptor = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(file_name);
if (file_descriptor == -1)
return (-1);
for (current_node = info->history; current_node; current_node = current_node->next)
{
print_fd(current_node->str, file_descriptor);
write_fd('\n', file_descriptor);
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
int i, last = 0, line_count = 0;
ssize_t file_descriptor, read_length, file_size = 0;
struct stat st;
char *data = NULL, *file_name = fetch_history_file(info);
if (!file_name)
return (0);
file_descriptor = open(file_name, O_RDONLY);
free(file_name);
if (file_descriptor == -1)
return (0);
if (!fstat(file_descriptor, &st))
file_size = st.st_size;
if (file_size < 2)
return (0);
data = malloc(sizeof(char) * (file_size + 1));
if (!data)
return (0);
read_length = read(file_descriptor, data, file_size);
data[file_size] = 0;
if (read_length <= 0)
return (free(data), 0);
close(file_descriptor);
for (i = 0; i < file_size; i++)
{
if (data[i] == '\n')
{
data[i] = 0;
create_history_list(info, data + last, line_count++);
last = i + 1;
}
}
if (last != i)
create_history_list(info, data + last, line_count++);
free(data);
info->hist_count = line_count;
while (info->hist_count-- >= HIST_MAX)
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
