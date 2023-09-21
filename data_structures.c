#include "header.h"
#include <stdio.h>
/**
* insert_node - Inserts a node at the beginning of the list.
* @hptr: Address of a pointer to the head node.
* @nodestr: String field of the node.
* @histnum: Node index utilized by history.
*
* Return: Pointer to the new head node.
*/
list_t *insert_node(list_t **hptr, const char *nodestr, int histnum)
{
list_t *new_head;
if (!hptr)
return (NULL);
new_head = malloc(sizeof(list_t));
if (!new_head)
return (NULL);
initialize_memory((void *)new_head, 0, sizeof(list_t));
new_head->histnum = histnum;
if (nodestr)
{
new_head->nodestr = _strdup(nodestr);
if (!new_head->nodestr)
{
free(new_head);
return (NULL);
}
}
new_head->next = *hptr;
*hptr = new_head;
return (new_head);
}
/**
* insert_node_end - Appends a node to the end of the list.
* @hptr: Address of a pointer to the head node.
* @nodestr: The string field of the node.
* @histnum: Index of the node used for history.
*
* Return: Pointer to the new node.
*/
list_t *insert_node_end(list_t **hptr, const char *nodestr, int histnum)
{
list_t *new_node, *node;
if (!hptr)
return (NULL);
node = *hptr;
new_node = malloc(sizeof(list_t));
if (!new_node)
return (NULL);
initialize_memory((void *)new_node, 0, sizeof(list_t));
new_node->histnum = histnum;
if (nodestr)
{
new_node->nodestr = _strdup(nodestr);
if (!new_node->nodestr)
{
free(new_node);
return (NULL);
}
}
if (node)
{
while (node->next)
node = node->next;
node->next = new_node;
}
else
*hptr = new_node;
return (new_node);
}
/**
* display_list_items_str - Prints only the str element of a list_t linked list.
* @firstnode: Pointer to the first node.
*
* Return: Size of list.
*/
size_t display_list_items_str(const list_t *firstnode)
{
size_t list_size = 0;
list_t *current_node = firstnode;
while (current_node)
{
_puts(current_node->nodestr ? current_node->nodestr : "(nil)");
_puts("\n");
current_node = current_node->next;
list_size++;
}
return (list_size);
}
/**
* remove_element_at_position - Removes a node at the specified index.
* @headp: Address of a pointer to the first node.
* @delindex: Index of the node to be deleted.
*
* Return: Returns 1 on successful deletion, and 0 on failure.
*/
int remove_element_at_position(list_t **headp, unsigned int delindex)
{
list_t *node, *prev_node;
unsigned int current_index = 0;
if (!headp || !*headp)
return (0);
if (!delindex)
{
node = *headp;
*headp = (*headp)->next;
free(node->nodestr);
free(node);
return (1);
}
node = *headp;
while (node)
{
if (current_index == delindex)
{
prev_node->next = node->next;
free(node->nodestr);
free(node);
return (1);
}
current_index++;
prev_node = node;
node = node->next;
}
return (0);
}
/**
* release_list - Releases all nodes within a list.
* @headp: Address of the pointer to the head node.
*
* Return: None (void).
*/
void release_list(list_t **headp)
{
list_t *node, *next_node, *head;
if (!headp || !*headp)
return;
head = *headp;
node = head;
while (node)
{
next_node = node->next;
free(node->nodestr);
free(node);
node = next_node;
}
*headp = NULL;
}
