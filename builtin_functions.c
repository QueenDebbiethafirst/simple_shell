#include "header.h"
/**
* exit_program - Terminate the shell.
* @info: A structure holding possible arguments. Maintains a consistent function prototype.
*
* Return: Exits with the specified exit status (0) unless info.argv[0] is not "exit".
*/
int exit_program(info_t *info)
{
int exit_code;
if (info->argv[1]) /* If there is an exit argument */
{
exit_code = str_to_int_with_error_handling(info->argv[1]);
if (exit_code == -1)
{
execution_status = 2;
output_error(info, "Illegal number: ");
output_error(info->argv[1]);
print_char('\n');
return (1);
}
err_code = str_to_int_with_error_handling(info->argv[1]);
return (-2);
}
err_code = -1;
return (-2);
}
/**
* switch_dir - Modifies the current directory of the process.
* @info: A structure that holds possible arguments, maintaining a consistent function prototype.
*
* Return: Always return 0.
*/
int switch_dir(info_t *info)
{
char *current_dir, *new_dir, buffer[1024];
int chdir_ret;
current_dir = getcwd(buffer, 1024);
if (!current_dir)
_puts("TODO: >>getcwd failure emsg here<<\n");
if (!info->argv[1])
{
new_dir = retrieve_env(info, "HOME=");
if (!new_dir)
chdir_ret = chdir((new_dir = retrieve_env(info, "PWD=")) ? new_dir : "/");
else
chdir_ret = chdir(new_dir);
}
else if (_strcmp(info->argv[1], "-") == 0)
{
if (!retrieve_env(info, "OLDPWD="))
{
_puts(current_dir);
_putchar('\n');
return (1);
}
_puts(retrieve_env(info, "OLDPWD="));
_putchar('\n');
chdir_ret = chdir((new_dir = retrieve_env(info, "OLDPWD=")) ? new_dir : "/");
}
else
chdir_ret = chdir(info->argv[1]);
if (chdir_ret == -1)
{
output_error(info, "can't cd to ");
output_error(info->argv[1]);
print_char('\n');
}
else
{
setenv(info, "OLDPWD", retrieve_env(info, "PWD="));
setenv(info, "PWD", getcwd(buffer, 1024));
}
return (0);
}
/**
* show_instructions - Displays shell instructions (not yet implemented).
* @info: A structure holding potential arguments, ensuring a consistent function prototype.
*
* Return: Always returns 0.
*/
int show_instructions(info_t *info)
{
char **arg_array = info->argv;
_puts("help call works. Function not yet implemented \n");
if (0)
_puts(*arg_array); /* temp att_unused workaround */
return (0);
}
