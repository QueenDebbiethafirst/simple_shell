#include "header.h"
/**
* check_command - Checks whether a file is an executable command.
* @info: The information struct.
* @filepath: The path to the file.
*
* Return: Returns 1 if the condition is true, and 0 otherwise.
*/
int check_command(info_t *info, char *filepath)
{
struct stat st;
(void)info;
if (!filepath || stat(filepath, &st))
return (0);
if (S_ISREG(st.st_mode))
return (1);
return (0);
}
/**
* duplicate_characters - Replicates characters.
* @pstr: The PATH string.
* @st: The starting index.
* @sp: The stopping index.
*
* Return: Returns a pointer to a new buffer.
*/
char *duplicate_characters(char *pstr, int st, int sp)
{
static char buf[1024];
int k = 0;
for (int i = st; i < sp; i++)
{
if (pstr[i] != ':')
buf[k++] = pstr[i];
}
buf[k] = 0;
return (buf);
}
/**
* locate_path - Finds the cmd in the PATH string.
* @info: The info struct.
* @pstr: The PATH string.
* @cmd: The cmd to find.
*
* Return: Full path of cmd if found or NULL.
*/
char *locate_path(info_t *info, char *pstr, char *cmd)
{
int i = 0, curr_pos = 0;
char *path;
if (!pstr)
return (NULL);
if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
{
if (check_command(info, cmd))
return (cmd);
}
while (1)
{
if (!pstr[i] || pstr[i] == ':')
{
path = duplicate_characters(pstr, curr_pos, i);
if (!*path)
_strcat(path, cmd);
else
{
_strcat(path, "/");
_strcat(path, cmd);
}
if (check_command(info, path))
return (path);
if (!pstr[i])
break;
curr_pos = i;
}
i++;
}
return (NULL);
}
