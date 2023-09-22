#include "header.h"

/**
 * main_shell_loop - Main loop of the shell.
 *
 * @info: A structure containing parameter and return information.
 * @av: The argument vector passed from the main() function.
 *
 * Returns: 0 on success, 1 on error, or an error code.
 */
int main_shell_loop(info_t *info, char **av)
{
    ssize_t read_result = 0;
    int builtin_ret = 0;
    
    while (1)
    {
        reset_data(info);
        
        if (command_line(info))
            _puts("$ ");
        
        print_char(CLEAR_BUFFER);
        
        read_result = fetch_input(info);
        
        if (read_result == -1 || builtin_ret == -2)
            break;
        
        save_data(info, av);
        
        builtin_ret = locate_builtin(info);
        
        if (builtin_ret == -1)
            find_command(info);
        
        if (!command_line(info) && execution_status)
            break;
        
        deallocate_info(info, 0);
    }
    
    record_history(info);
    deallocate_info(info, 1);
    
    if (builtin_ret == -2)
    {
        if (err_code == -1)
            exit(execution_status);
        exit(err_code);
    }
    
    return (builtin_ret);
}

/**
 * locate_and_execute_command - Locates and executes a command.
 *
 * @info: A structure containing input and output parameters.
 */
void locate_and_execute_command(info_t *info)
{
    char *path = NULL;
    int i, k;
    
    info->path = info->argv[0];
    
    if (info->linecount_flag == 1)
    {
        info->line_count++;
        info->linecount_flag = 0;
    }
    
    for (i = 0, k = 0; info->arg[i]; i++)
    {
        if (!check_delimiter(info->arg[i], " \t\n"))
            k++;
    }
    
    if (!k)
        return;
    
    path = locate_path(info, retrieve_env(info, "PATH="), info->argv[0]);
    
    if (path)
    {
        info->path = path;
        locate_command(info);
    }
    else
    {
        if ((command_line(info) || retrieve_env(info, "PATH=") || info->argv[0][0] == '/'))
            locate_command(info);
        else if (*(info->arg) != '\n')
        {
            execution_status = 127;
            output_error(info, "not found\n");
        }
    }
}

/**
 * locate_command - Creates a new execution thread through forking to run a command.
 *
 * @info: A structure containing parameters and return information.
 */
void locate_command(info_t *info)
{
    pid_t child_pid;
    
    child_pid = fork();
    
    if (child_pid == -1)
    {
        perror("Error:");
        return;
    }
    
    if (child_pid == 0)
    {
        if (execve(info->path, info->argv, retrieve_env(info)) == -1)
        {
            deallocate_info(info, 1);
            
            if (errno == EACCES)
                exit(126);
            
            exit(1);
        }
    }
    else
    {
        int status;
        wait(&status);
        
        if (WIFEXITED(status))
        {
            execution_status = WEXITSTATUS(status);
            
            if (execution_status == 126)
                output_error(info, "Permission denied\n");
        }
    }
}
