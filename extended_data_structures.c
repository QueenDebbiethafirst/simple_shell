#include "header.h"
/**
* get_list_length - Calculates the length of a linked list.
* @listHead: Pointer to the first node of the list.
*
* Return: The size of the list.
*/
size_t get_list_length(const list_t *listHead)
{
size_t listSize = 0;
while (listHead)
{
listHead = listHead->next;
listSize++;
}
return (listSize);
}
/**
* convert_list_to_strings - Converts the list->str elements into an array of strings.
* @listPtr: Pointer to the first node of the list.
*
* Return: An array containing the converted strings.
*/
char **convert_list_to_strings(list_t *listPtr)
{
list_t *node = listPtr;
size_t listSize = get_list_length(listPtr), i;
char **strings;
char *str;
if (!listPtr || !listSize)
return (NULL);
strings = malloc(sizeof(char *) * (listSize + 1));
if (!strings)
return (NULL);
for (i = 0; node; node = node->next, i++)
{
str = malloc(_strlen(node->nodestr) + 1);
if (!str)
{
for (size_t j = 0; j < i; j++)
free(strings[j]);
free(strings);
return (NULL);
}
str = _strcpy(str, node->nodestr);
strings[i] = str;
}
strings[i] = NULL;
return (strings);
}
/**
* display_list_items - Displays all elements within a linked list of type list_t.
* @listHead: Pointer to the first node of the list.
*
* Return: The size of the list.
*/
size_t display_list_items(const list_t *listHead)
{
size_t listSize = 0;
while (listHead)
{
_puts(parse_number(listHead->histnum, 10, 0));
_putchar(':');
_putchar(' ');
_puts(listHead->nodestr ? listHead->nodestr : "(nil)");
_puts("\n");
listHead = listHead->next;
listSize++;
}
return (listSize);
}
/**
* element_starts_with - Retrieves a node whose string begins with a given prefix.
* @listPtr: Pointer to the head of the list.
* @prefixString: String to compare as a prefix.
* @charToCompare: The succeeding character after the prefix to compare.
*
* Return: Returns the matching node or null if no match is found.
*/
list_t *element_starts_with(list_t *listPtr, char *prefixString, char charToCompare)
{
char *prefixMatch = NULL;
while (listPtr)
{
prefixMatch = starts_with(listPtr->nodestr, prefixString);
if (prefixMatch && ((charToCompare == -1) || (*prefixMatch == charToCompare)))
return (listPtr);
listPtr = listPtr->next;
}
return (NULL);
}
/**
* locate_element_index - Retrieves the index of a node within a list.
* @listHead: Pointer to the head of the list.
* @node: Pointer to the specific node.
*
* Return: Returns the index of the node, or -1 if not found.
*/
ssize_t locate_element_index(list_t *listHead, list_t *node)
{
size_t index = 0;
while (listHead)
{
if (listHead == node)
return (index);
listHead = listHead->next;
index++;
}
return (-1);
}
