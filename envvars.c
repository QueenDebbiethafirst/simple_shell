#include "header.h"
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
buf = malloc(_strlen(envvar) + _strlen(envval) + 2);
if (!buf)
return (1);
_strcpy(buf, envvar);
_strcat(buf, "=");
_strcat(buf, envval);
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
