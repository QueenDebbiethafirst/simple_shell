#include "header.h"
/**
* initialize_memory - Fills a memory area with a specific byte value.
* @memptr: Pointer to the memory area.
* @fillbyte: The byte value to fill @memptr with.
* @numbytes: The number of bytes to fill.
*
* Return: A pointer to the modified memory area (@memptr).
*/
char *initialize_memory(char *memptr, char fillbyte, unsigned int numbytes)
{
unsigned int i;
for (i = 0; i < numbytes; i++)
memptr[i] = fillbyte;
return (memptr);
}
/**
* free_file - Frees memory occupied by an array of strings.
* @strarrptr: Pointer to a string array.
*/
void free_file(char **strarrptr)
{
char **arr = strarrptr;
if (!strarrptr)
return;
while (*strarrptr)
free(*strarrptr++);
free(arr);
}
/**
* _realloc - Resizes a memory block.
* @memblockptr: Pointer to a previously allocated memory block.
* @oldsize: Size in bytes of the original block.
* @newsize: Size in bytes of the new block.
*
* Return: Returns a pointer to the adjusted memory block.
*/
void *_realloc(void *memblockptr, unsigned int oldsize, unsigned int newsize)
{
char *charptr;
if (!memblockptr)
return (malloc(newsize));
if (!newsize)
return (free(memblockptr), NULL);
if (newsize == oldsize)
return (memblockptr);
charptr = malloc(newsize);
if (!charptr)
return (NULL);
oldsize = oldsize < newsize ? oldsize : newsize;
while (oldsize--)
charptr[oldsize] = ((char *)memblockptr)[oldsize];
free(memblockptr);
return (charptr);
}
