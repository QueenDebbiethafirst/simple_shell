#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "header.h"

/* Function to perform some operation */
void performOperation() 
{
    int* data = malloc(sizeof(int));
    if (data == NULL) 
    {
        fprintf(stderr, "Error: Failed to allocate memory\n");
        exit(1);
    }

    *data = 10;

    printf("Data: %d\n", *data);

    free(data);
}

int main() 
{
    performOperation();

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * struct list_s - singly linked list
 * @nodestr: string - (malloc'ed string)
 * @histnum: node index utilized by history
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 * for Holberton project
 */
typedef struct list_s
{
    char *nodestr;
    int histnum;
    struct list_s *next;
} list_t;

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

    new_head->histnum = histnum;
    new_head->nodestr = strdup(nodestr);
    if (!new_head->nodestr)
    {
        free(new_head);
        return (NULL);
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

    new_node = malloc(sizeof(list_t));
    if (!new_node)
        return (NULL);

    new_node->histnum = histnum;
    new_node->nodestr = strdup(nodestr);
    if (!new_node->nodestr)
    {
        free(new_node);
        return (NULL);
    }

    if (*hptr)
    {
        node = *hptr;
        while (node->next)
            node = node->next;
        node->next = new_node;
    }
    else
    {
        *hptr = new_node;
    }

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
    const list_t *current_node = firstnode;

    while (current_node)
    {
        printf("%s\n", current_node->nodestr ? current_node->nodestr : "(nil)");
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

    if (delindex == 0)
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
    list_t *node, *next_node;

    if (!headp || !*headp)
        return;

    node = *headp;
    while (node)
    {
        next_node = node->next;
        free(node->nodestr);
        free(node);
        node = next_node;
    }

    *headp = NULL;
}
