#include "header.h"
/**
* initialize_info_data - Initializes the info_t structure.
* @info: Address of the structure.
*/
void initialize_info_data(info_t *info)
{
info->arguments = NULL;
info->arg_vector = NULL;
info->executable_path = NULL;
info->arg_count = 0;
}
/**
* populate_info_data - Populates the info_t structure.
* @info: Address of the structure.
* @args: Argument vector.
*/
void populate_info_data(info_t *info, char **args)
{
int i = 0;
info->program_name = args[0];
if (info->arguments)
{
info->arg_vector = tokenize(info->arguments, " \t");
if (!info->arg_vector)
{
info->arg_vector = malloc(sizeof(char *) * 2);
if (info->arg_vector)
{
info->arg_vector[0] = duplicate_string(info->arguments);
info->arg_vector[1] = NULL;
}
}
for (i = 0; info->arg_vector && info->arg_vector[i]; i++)
{
}
info->arg_count = i;
substitute_aliases(info);
substitute_variables(info);
}
}
/**
* free_info_data - Releases memory occupied by fields in the info_t struct.
* @info: Address of the struct to be freed.
* @freeall: Set to true if all fields need to be freed.
*/
void free_info_data(info_t *info, int freeall)
{
free_string_array(info->arg_vector);
info->arg_vector = NULL;
info->executable_path = NULL;
if (freeall)
{
if (!info->command_buffer)
{
free(info->arguments);
}
if (info->environment_data)
{
release_list(&(info->environment_data));
}
if (info->history_data)
{
release_list(&(info->history_data));
}
if (info->alias_data)
{
release_list(&(info->alias_data));
}
free_string_array(info->environment_strings);
info->environment_strings = NULL;
free_buffer((void **)info->command_buffer);
if (info->input_stream > 2)
{
close(info->input_stream);
}
putchar(CLEAR_BUFFER);
}
}
