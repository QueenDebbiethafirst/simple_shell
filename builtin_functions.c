#include "header.h"
#include <stdio.h>
#include <stdlib.h>

int main() 
{
    char buffer[10];
    int num = 0;
    int *ptr = NULL;

    /*Read input from user*/
    printf("Enter a number: ");
    fgets(buffer, sizeof(buffer), stdin);
    num = atoi(buffer);

    /*Allocate memory for the pointer*/
    ptr = (int*)malloc(sizeof(int));
    if (ptr == NULL) {
        printf("Failed to allocate memory\n");
        return (1);
    }

    /*Assign value to the pointer*/
    *ptr = num;

    /* Print the value*/
    printf("Value: %d\n", *ptr);

    /*Free the allocated memory*/
    free(ptr);

    return (0);
}

#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct info_s 
{
    char **argv;
} info_t;

void output_error(info_t *info, char *msg) 
{
    fprintf(stderr, "%s", msg);
}

int str_to_int_with_error_handling(char *str) 
{
    char *endptr;
    int num = strtol(str, &endptr, 10);
    if (*endptr != '\0') 
    {
        return (-1);
    }
    return (num);
}

void print_char(char c) 
{
    putchar(c);
}

char* retrieve_env(info_t *info, char *prefix) 
{
    int i = 0;
    while (info->argv[i] != NULL) 
    {
        if (strncmp(info->argv[i], prefix, strlen(prefix)) == 0) 
        {
            return info->argv[i] + strlen(prefix);
        }
        i++;
    }
    return (NULL);
}

void _puts(char *str) 
{
    printf("%s", str);
}

int _strcmp(char *s1, char *s2) 
{
    return (strcmp(s1, s2));
}

int exit_program(info_t *info) 
{
    int exit_code, err_code, execution_status;
    if (info->argv[1]) 
    {
        exit_code = str_to_int_with_error_handling(info->argv[1]);
        if (exit_code == -1) 
        {
            execution_status = 2;
            output_error(info, "Illegal number: ");
            output_error(info, info->argv[1]);
            print_char('\n');
            return (1);
        }
        err_code = str_to_int_with_error_handling(info->argv[1]);
        return (-2);
    }
    err_code = -1;
    return (-2);
}

int switch_dir(info_t *info) 
{
    char *current_dir, *new_dir, buffer[1024];
    int chdir_ret;
    current_dir = getcwd(buffer, 1024);
    if (!current_dir) 
    {
        output_error(info, "TODO: >>getcwd failure emsg here<<\n");
    }
    if (!info->argv[1]) 
    {
        new_dir = retrieve_env(info, "HOME=");
        if (!new_dir) 
        {
            chdir_ret = chdir((new_dir = retrieve_env(info, "PWD=")) ? new_dir : "/");
        } else 
        {
            chdir_ret = chdir(new_dir);
        }
    } else if (_strcmp(info->argv[1], "-") == 0) 
    {
        if (!retrieve_env(info, "OLDPWD=")) 
        {
            _puts(current_dir);
            print_char('\n');
            return (1);
        }
        _puts(retrieve_env(info, "OLDPWD="));
        print_char('\n');
        chdir_ret = chdir((new_dir = retrieve_env(info, "OLDPWD=")) ? new_dir : "/");
    } 
    else 
    {
        chdir_ret = chdir(info->argv[1]);
    }
    if (chdir_ret == -1) 
    {
        output_error(info, "can't cd to ");
        output_error(info, info->argv[1]);
        print_char('\n');
    } else 
    {
        setenv("OLDPWD", retrieve_env(info, "PWD="), 1);
        setenv("PWD", getcwd(buffer, 1024), 1);
    }
    return (0);
}

int show_instructions(info_t *info) 
{
    char **arg_array = info->argv;
    _puts("help call works. Function not yet implemented \n");
    if (0) 
    {
        _puts(*arg_array);
    }
    return (0);
}
