#include "header.h"
#include <stdio.h> 
/**
* buffer_input - Buffer linked commands.
* @info: Parameter structure.
* @buf: Address of the buffer.
* @lengthaddr: Address of the length variable.
*
* Return: Returns the number of bytes read.
*/
ssize_t buffer_input(info_t *info, char **buf, size_t *lengthaddr)
{
ssize_t bytesRead;
size_t len_p;
if (!*lengthaddr) /* If nothing left in the buffer, fill it */
{
free(*buf);
*buf = NULL;
signal(SIGINT, sigintHandler);
#if USEread_line
bytesRead = getline(buf, &len_p, stdin);
#else
bytesRead = read_line(info, buf, &len_p);
#endif
if (bytesRead > 0)
{
if ((*buf)[bytesRead - 1] == '\n')
{
(*buf)[bytesRead - 1] = '\0'; /* Remove trailing newline */
bytesRead--;
}
info->linecount_flag = 1;
eliminate_comments(*buf);
create_history_list(info, *buf, info->histcount++);
}
}
return (bytesRead);
}
/**
* fetch_input - Retrieves a line of text excluding the newline character.
* @info: Parameter structure.
*
* Return: Number of bytes read.
*/
ssize_t fetch_input(info_t *info)
{
static char *buf; /* The ';' command chain buffer */
static size_t bufIndex, nextCommandIndex, bufLen;
ssize_t bytesRead;
char **bufPtr = &(info->arg);
_putchar(CLEAR_BUFFER);
bytesRead = buffer_input(info, &buf, &bufLen);
if (bytesRead == -1) /* EOF */
return (-1);
if (bufLen) /* We have commands left in the chain buffer */
{
nextCommandIndex = bufIndex; /* Initialize a new iterator to the current buf position */
char *currentCommand = buf + bufIndex; /* Get a pointer for return */
evaluate_chain(info, buf, &nextCommandIndex, bufIndex, bufLen);
while (nextCommandIndex < bufLen) /* Iterate to semicolon or end */
{
if (check_variable_link(info, buf, &nextCommandIndex))
break;
nextCommandIndex++;
}
bufIndex = nextCommandIndex + 1; /* Increment past the nulled ';' */
if (bufIndex >= bufLen) /* Reached the end of the buffer? */
{
bufIndex = bufLen = 0; /* Reset position and length */
info->cmd_buf_type = CMD_NORM;
}

*bufPtr = currentCommand; /* Pass back a pointer to the current command position */
return (_strlen(currentCommand)); /* Return the length of the current command */
}
*bufPtr = (buf); /* Else not a chain, pass back the buffer from read_line() */
return (bytesRead); /* Return the length of the buffer from read_line() */
}
/**
* read_buffer - Reads data into a buffer.
* @info: A parameter structure.
* @buf: The buffer for storing data.
* @bufsize: The size of the buffer.
*
* Return: The value 'bytesRead'.
*/
ssize_t read_buffer(info_t *info, char *buf, size_t *bufsize)
{
ssize_t bytesRead;
if (*bufsize)
return (0);
bytesRead = read(info->input_stream, buf, READ_BUFFER_SIZE);
if (bytesRead >= 0)
*bufsize = bytesRead;
return (bytesRead);
}
/**
* read_line - Retrieves the next line of input from STDIN.
* @info: A parameter structure.
* @bufptr: Address of the pointer to the buffer, either preallocated or NULL.
* @size: Size of the preallocated 'bufptr' buffer if not NULL.
*
* Return: Returns 's'.
*/
int read_line(info_t *info, char **bufptr, size_t *size)
{
static char buf[READ_BUFFER_SIZE];
static size_t bufIndex, bufLen;
size_t k;
ssize_t bytesRead, totalBytesRead;
char *p, *new_p, *c;
p = *bufptr;
if (p && size)
totalBytesRead = *size;
if (bufIndex == bufLen)
bufIndex = bufLen = 0;
bytesRead = read_buffer(info, buf, &bufLen);
if (bytesRead == -1 || (bytesRead == 0 && bufLen == 0))
return (-1);
c = locate_char(buf + bufIndex, '\n');
k = c ? 1 + (unsigned int)(c - buf) : bufLen;
new_p = _realloc(p, totalBytesRead, totalBytesRead ? totalBytesRead + k : k + 1);
if (!new_p) /* MALLOC FAILURE! */
return (p ? free(p), -1 : -1);
if (totalBytesRead)
concatenate_string(new_p, buf + bufIndex, k - bufIndex);
else
copy_string(new_p, buf + bufIndex, k - bufIndex + 1);
totalBytesRead += k - bufIndex;
bufIndex = k;
p = new_p;
if (size)
*size = totalBytesRead;
*bufptr = p;
return (totalBytesRead);
}
/**
* sigintHandler - Handles the blocking of the Ctrl-C signal.
* @signum: The signal number.
*
* Return: Returns void.
*/
void sigintHandler(__attribute__((unused)) int signum)
{
_puts("\n");
_puts("$ ");
_putchar(CLEAR_BUFFER);
}
