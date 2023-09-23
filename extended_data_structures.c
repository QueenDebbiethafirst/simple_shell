#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "header.h"

/* Function to calculate the length of a list */
int calculateListLength(Node* head) 
{
    int length = 0;
    Node* current = head;

    while (current != NULL) 
    {
        length++;
        current = current->next;
    }

    return (length);
}

/* Function to handle errors */
void handleError(const char* errorMessage) 
{
    fprintf(stderr, "Error: %s\n", errorMessage);
    exit(1);
}

int main() {
    Node* head = NULL;

    // Code logic here...

    /*Free memory allocated for the list*/
    Node* current = head;
    while (current != NULL) 
    {
        Node* temp = current;
        current = current->next;
        free(temp);
    }

    return (0);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
* struct list_s - singly linked list
* @nodestr: string - (malloc'ed string)
* @histnum: number of elements in the list
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
* get_list_length - Calculates the length of a linked list.
* @listHead: Pointer to the first node of the list.
*
* Return: The size of the list.
*/
size_t get_list_length(const list_t *listHead)
{
    size_t listSize = 0;
    const list_t *current = listHead;

    while (current)
    {
        current = current->next;
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
    size_t listSize = get_list_length(listPtr);
    char **strings;
    char *str;
    size_t i;

    if (!listPtr || listSize == 0)
        return (NULL);

    strings = malloc(sizeof(char *) * (listSize + 1));
    if (!strings)
        return (NULL);

    for (i = 0; node; node = node->next, i++)
    {
        str = malloc(strlen(node->nodestr) + 1);
        if (!str)
        {
            for (size_t j = 0; j < i; j++)
                free(strings[j]);
            free(strings);
            return (NULL);
        }
        strcpy(str, node->nodestr);
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
    const list_t *current = listHead;

    while (current)
    {
        printf("%d: ", current->histnum);
        printf("%s\n", current->nodestr ? current->nodestr : "(nil)");
        current = current->next;
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
    list_t *current = listPtr;

    while (current)
    {
        prefixMatch = strstr(current->nodestr, prefixString);
        if (prefixMatch && ((charToCompare == -1) || (*prefixMatch == charToCompare)))
            return (current);
        current = current->next;
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
    list_t *current = listHead;

    while (current)
    {
        if (current == node)
            return (index);
        current = current->next;
        index++;
    }

    return (-1);
}
