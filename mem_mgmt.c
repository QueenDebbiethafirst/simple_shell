#include "header.h"
/**
* free_buffer - Releases memory and sets the pointer to NULL.
* @ptrToFree: Address of the pointer to be freed.
*
* Return: Returns 1 if memory was freed, 0 otherwise.
*/
int free_buffer(void **ptrToFree)
{
if (ptrToFree && *ptrToFree)
{
free(*ptrToFree);
*ptrToFree = NULL;
return (1);
}
return (0);

