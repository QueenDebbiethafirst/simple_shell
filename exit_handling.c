#include "header.h"
/**
* copy_string - Duplicates a string.
* @copydest: The destination string for copying.
* @appsrc: The source string.
* @copynum: The number of characters to copy.
*
* Return: The resulting concatenated string.
*/
char *copy_string(char *copydest, const char *appsrc, int copynum)
{
int i;
char *result = copydest;
for (i = 0; appsrc[i] != '\0' && i < copynum - 1; i++)
{
copydest[i] = appsrc[i];
}
while (i < copynum)
{
copydest[i++] = '\0';
}
return (result);
}
/**
* concatenate_string - Appends one string's content to another.
* @dest: The destination string.
* @appsrc: The source string to be appended.
* @copynum: The maximum number of bytes to be used.
*
* Return: The resulting concatenated string.
*/
char *concatenate_string(char *dest, const char *appsrc, int copynum)
{
int i, j;
char *result = dest;
for (i = 0; dest[i] != '\0'; i++)
{
}
for (j = 0; appsrc[j] != '\0' && j < copynum; j++)
{
dest[i++] = appsrc[j];
}
if (j < copynum)
{
dest[i] = '\0';
}
Return (result);
}
/**
* locate_char - Finds the position of a character in a string.
* @searchstr: The string to search within.
* @findchars: The character to locate.
*
* Return: A pointer to the memory area of 'searchstr', or NULL if 'findchars' is not found.
*/
char *locate_char(const char *searchstr, char findchars)
{
do {
if (*searchstr == findchars)
{
return ((char *)searchstr);
}
} while (*searchstr++ != '\0');
return (NULL);
}
