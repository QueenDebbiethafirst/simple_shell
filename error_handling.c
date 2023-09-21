#include "header.h"
#include <stdio.h>
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
return ();
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
static int i;
static char buf[WRITE_BUF_SIZE];
if (wc == CLEAR_BUFFER || i >= WRITE_BUF_SIZE)
{
write(2, buf, i);
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
static int i;
static char buf[WRITE_BUF_SIZE];
if (wc == CLEAR_BUFFER || i >= WRITE_BUF_SIZE)
{
write(fd, buf, i);
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
