#include <stdio.h>
#include <stdlib.h>

#include "header.h"

void someFunction(int param);

int main(void) 
{
    int variable = 0;
    someFunction(variable);
    return (0);
}

void someFunction(int param) 
{
    printf("Parameter value: %d\n", param);
}

#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#include "header.h"

#define WRITE_BUF_SIZE 1024
#define CLEAR_BUFFER '\0'

int write_char(char wc);
int write_fd(char wc, int fd);
int print_fd(char *output_str, int fd);

/**
 * output_error - Prints the given string.
 * @output_str: The string to be displayed.
 *
 * Return: None.
 */
void output_error(char *output_str)
{
    int index = 0;

    if (!output_str)
        return;

    while (output_str[index] != '\0')
    {
        write_char(output_str[index]);
        index++;
    }
}

/**
 * write_char - Writes the character 'wc' to the standard error stream.
 * @wc: The character to be written.
 *
 * Return: Returns 1 on success.
 *         If an error occurs, returns -1 and sets the 'errno' accordingly.
 */
int write_char(char wc)
{
    static int i = 0;
    static char buf[WRITE_BUF_SIZE];

    if (wc == CLEAR_BUFFER || i >= WRITE_BUF_SIZE)
    {
        if (write(2, buf, i) == -1)
        {
            perror("write_char");
            return (-1);
        }
        i = 0;
    }

    if (wc != CLEAR_BUFFER)
        buf[i++] = wc;

    return (1);
}

/**
 * write_fd - Writes the character 'wc' to the specified file descriptor 'fd'.
 * @wc: The character to be written.
 * @fd: The file descriptor for writing.
 *
 * Return: Returns 1 on successful write.
 *         If an error occurs, returns -1 and sets the relevant errno value.
 */
int write_fd(char wc, int fd)
{
    static int i = 0;
    static char buf[WRITE_BUF_SIZE];

    if (wc == CLEAR_BUFFER || i >= WRITE_BUF_SIZE)
    {
        if (write(fd, buf, i) == -1)
        {
            perror("write_fd");
            return (-1);
        }
        i = 0;
    }

    if (wc != CLEAR_BUFFER)
        buf[i++] = wc;

    return (1);
}

/**
 * print_fd - Outputs the provided string to the specified file descriptor.
 * @output_str: The string to be shown.
 * @fd: The file descriptor for output.
 *
 * Return: The number of characters written.
 */
int print_fd(char *output_str, int fd)
{
    int index = 0;

    if (!output_str)
        return (0);

    while (output_str[index])
    {
        index += write_fd(output_str[index], fd);
    }

    return (index);
}
