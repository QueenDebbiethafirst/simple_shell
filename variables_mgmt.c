#include "header.h"
/**
* user_environment - Displays the current environment.
* @info: A structure holding potential arguments, ensuring a consistent function prototype.
*
* Return: Always returns 0.
*/
int user_environment(info_t *info)
{
display_list_items_str(Info_env_data);
return (0);
}
/**
* retrieve_env - Retrieves the value of an environment variable.
* @info: A structure holding potential arguments, maintaining consistency.
* @env_var_name: Name of the environment variable.
*
* Return: Returns the corresponding value.
*/
char *retrieve_env(info_t *info, const char *env_var_name)
{
list_t *node = Info_env_data;
char *value;
while (node)
{
value = starts_with(node->str, env_var_name);
if (value && *value)
return (value);
node = node->next;
}
return (NULL);
}
/**
* custom_set_environment - Establishes a new environment variable or modifies an existing one.
* @info: A structure holding potential arguments, ensuring a consistent function prototype.
*
* Return: Always returns 0.
*/
int custom_set_environment(info_t *info)
{
if (info->argc != 3)
{
output_error("Incorrect number of arguments\n");
return (1);
}
if (setenv(info, info->argv[1], info->argv[2]))
return (0);
return (1);
}
/**
* delete_env_variable - Deletes an environment variable.
* @info: A structure holding potential arguments, ensuring a constant function prototype.
*
* Return: Always returns 0.
*/
int delete_env_variable(info_t *info)
{
int i;
if (info->argc == 1)
{
output_error("Too few arguments.\n");
return (1);
}
for (i = 1; i < info->argc; i++)
unsetenv(info, info->argv[i]);
return (0);
}
/**
* fill_env_list - Fills an environment linked list.
* @info: A structure holding potential arguments, ensuring a consistent function prototype.
*
* Return: Always returns 0.
*/
int fill_env_list(info_t *info)
{
list_t *node = NULL;
size_t i;
for (i = 0; environ[i]; i++)
insert_node_end(&node, environ[i], 0);
Info_env_data = node;
return (0);
}
