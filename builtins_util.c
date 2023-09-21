#include "header.h"
#include <stdio.h>
/**
* user_history - Presents the history list with each command on a separate line,
*                accompanied by line numbers that commence at 0.
* @info: A structure encompassing potential arguments, employed for upholding a consistent function prototype.
*
* Return: Always returns 0.
*/
int user_history(info_t *info)
{
display_list_items(info->history);
return (0);
}
/**
* delete_alias - Assigns an alias to a string.
* @info: A parameter structure.
* @alias_str: The alias string to be assigned.
*
* Return: Returns 0 upon success, and 1 if an error occurs.
*/
int delete_alias(info_t *info, char *alias_str)
{
char *equals_sign, temp_char;
int ret;
equals_sign = locate_char(alias_str, '=');
if (!equals_sign)
return (1);
temp_char = *equals_sign;
*equals_sign = '\0';
ret = remove_element_at_position(&(info->alias),
locate_element_index(info->alias, alias_str));
*equals_sign = temp_char;
return (ret);
}
/**
* establish_alias - Assigns an alias to a string.
* @info: A parameter structure.
* @alias_str: The string to be aliased.
*
* Return: Returns 0 upon success, 1 upon encountering an error.
*/
int establish_alias(info_t *info, char *alias_str)
{
char *equals_sign;
equals_sign = locate_char(alias_str, '=');
if (!equals_sign)
return (1);
if (!*++equals_sign)
return (delete_alias(info, alias_str));
delete_alias(info, alias_str);
return (insert_node_end(&(info->alias), alias_str, 0) == NULL);
}
/**
* display_alias - Displays an alias string.
* @node: The alias node to be printed.
*
* Return: Returns 0 on success, and 1 on error.
*/
int display_alias(list_t *node)
{
char *equals_sign, *alias_start;
if (node)
{
equals_sign = locate_char(node->str, '=');
for (alias_start = node->str; alias_start < equals_sign; alias_start++)
_putchar(*alias_start);
_putchar('=');
_puts(equals_sign + 1);
_puts("\n");
return (0);
}
return (1);
}
/**
* user_alias - Simulates the behavior of the 'alias' built-in command.
* @info: A structure containing potential arguments, ensuring consistent function prototype.
*
* Return: Always returns 0.
*/
int user_alias(info_t *info)
{
int i;
char *equals_sign;
list_t *node;
if (info->argc == 1)
{
node = info->alias;
while (node)
{
display_alias(node);
node = node->next;
}
return (0);
}
for (i = 1; info->argv[i]; i++)
{
equals_sign = locate_char(info->argv[i], '=');
if (equals_sign)
establish_alias(info, info->argv[i]);
else
display_alias(element_starts_with(info->alias, info->argv[i], '='));
}
return (0);
}
