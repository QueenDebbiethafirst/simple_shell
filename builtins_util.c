#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "header.h"

/* Function to validate input */
int validateInput(int input) {
    if (input < 0 || input > 100) {
        printf("Invalid input. Please enter a number between 0 and 100.\n");
        return 0;
    }
    return 1;
}

/* Function to concatenate two strings */
char* concatenateStrings(const char* str1, const char* str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    char* result = malloc(len1 + len2 + 1);
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}

/* Function to perform some logic */
int performLogic(int input) {
    if (input % 2 == 0) {
        return input * 2;
    } else {
        return input * 3;
    }
}

/* Function to manipulate a string */
char* manipulateString(const char* str) {
    int len = strlen(str);
    char* result = malloc(len + 1);
    for (int i = 0; i < len; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            result[i] = str[i] - 32;
        } else {
            result[i] = str[i];
        }
    }
    result[len] = '\0';
    return result;
}

/* Function to fix code issues */
void fixCode() {
    int input;
    printf("Enter a number between 0 and 100: ");
    scanf("%d", &input);

    if (!validateInput(input)) {
        return;
    }

    char* str1 = "Hello";
    char* str2 = "World";
    char* concatenated = concatenateStrings(str1, str2);
    printf("Concatenated string: %s\n", concatenated);
    free(concatenated);

    int result = performLogic(input);
    printf("Result: %d\n", result);

    char* str = "hello";
    char* manipulated = manipulateString(str);
    printf("Manipulated string: %s\n", manipulated);
    free(manipulated);
}

int main() {
    fixCode();
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * struct list_s - singly linked list
 * @str: string - (malloc'ed string)
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 * for Holberton project
 */
typedef struct list_s
{
    char *str;
    struct list_s *next;
} list_t;

/**
 * struct info_s - structure to hold command information
 * @argc: number of arguments
 * @argv: array of arguments
 * @history: linked list of command history
 * @alias: linked list of aliases
 *
 * Description: structure to hold command information
 * for Holberton project
 */
typedef struct info_s
{
    int argc;
    char **argv;
    list_t *history;
    list_t *alias;
} info_t;

/**
 * display_list_items - Prints all items in a linked list
 * @head: Pointer to the head of the list
 */
void display_list_items(list_t *head)
{
    list_t *current = head;

    while (current != NULL)
    {
        printf("%s\n", current->str);
        current = current->next;
    }
}

/**
 * remove_element_at_position - Removes an element at a given position in a linked list
 * @head: Pointer to the head of the list
 * @index: Index of the element to be removed
 *
 * Return: 0 on success, 1 on failure
 */
int remove_element_at_position(list_t **head, int index)
{
    list_t *current, *prev;
    int i;

    if (*head == NULL)
        return (1);

    if (index == 0)
    {
        current = *head;
        *head = current->next;
        free(current->str);
        free(current);
        return (0);
    }

    prev = *head;
    current = prev->next;
    for (i = 1; current != NULL && i < index; i++)
    {
        prev = current;
        current = current->next;
    }

    if (current == NULL)
        return (1);

    prev->next = current->next;
    free(current->str);
    free(current);

    return (0);
}

/**
 * locate_char - Locates the first occurrence of a character in a string
 * @str: The string to search
 * @c: The character to locate
 *
 * Return: Pointer to the first occurrence of the character,
 *         or NULL if the character is not found
 */
char *locate_char(char *str, char c)
{
    while (*str)
    {
        if (*str == c)
            return (str);
        str++;
    }
    return (NULL);
}

/**
 * locate_element_index - Locates the index of an element in a linked list
 * @head: Pointer to the head of the list
 * @str: The element to locate
 *
 * Return: Index of the element, or -1 if the element is not found
 */
int locate_element_index(list_t *head, char *str)
{
    list_t *current = head;
    int index = 0;

    while (current != NULL)
    {
        if (strcmp(current->str, str) == 0)
            return (index);
        current = current->next;
        index++;
    }

    return (-1);
}

/**
 * insert_node_end - Inserts a new node at the end of a linked list
 * @head: Pointer to the head of the list
 * @str: The string to be inserted
 * @index: The index at which the node should be inserted
 *
 * Return: Pointer to the newly inserted node, or NULL on failure
 */
list_t *insert_node_end(list_t **head, char *str, int index)
{
    list_t *new_node, *current;
    int i;

    new_node = malloc(sizeof(list_t));
    if (new_node == NULL)
        return (NULL);

    new_node->str = strdup(str);
    if (new_node->str == NULL)
    {
        free(new_node);
        return (NULL);
    }

    if (*head == NULL)
    {
        *head = new_node;
        new_node->next = NULL;
        return (new_node);
    }

    if (index == 0)
    {
        new_node->next = *head;
        *head = new_node;
        return (new_node);
    }

    current = *head;
    for (i = 1; current->next != NULL && i < index; i++)
        current = current->next;

    new_node->next = current->next;
    current->next = new_node;

    return (new_node);
}

/**
 * _putchar - Writes a character to stdout
 * @c: The character to be written
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
    return (write(1, &c, 1));
}

/**
 * _puts - Prints a string to stdout
 * @str: The string to be printed
 */
void _puts(char *str)
{
    while (*str)
    {
        _putchar(*str);
        str++;
    }
}

/**
 * display_alias - Displays an alias string
 * @node: The alias node to be printed
 *
 * Return: 0 on success, 1 on error
 */
int display_alias(list_t *node)
{
    char *equals_sign, *alias_start;

    if (node != NULL)
    {
        equals_sign = locate_char(node->str, '=');
        for (alias_start = node->str; alias_start < equals_sign; alias_start++)
            _putchar(*alias_start);
        _putchar('=');
        _puts(equals_sign + 1);
        _puts("\n");
        return (0);
    }

    return (1);
}

/**
 * user_history - Presents the history list with each command on a separate line,
 *                accompanied by line numbers that commence at 0.
 * @info: A structure encompassing potential arguments, employed for upholding a consistent function prototype.
 *
 * Return: Always returns 0.
 */
int user_history(info_t *info)
{
    display_list_items(info->history);
    return (0);
}

/**
 * delete_alias - Deletes an alias from the alias list
 * @info: A parameter structure
 * @alias_str: The alias string to be deleted
 *
 * Return: Returns 0 upon success, and 1 if an error occurs
 */
int delete_alias(info_t *info, char *alias_str)
{
    char *equals_sign, temp_char;
    int ret;

    equals_sign = locate_char(alias_str, '=');
    if (!equals_sign)
        return (1);

    temp_char = *equals_sign;
    *equals_sign = '\0';
    ret = remove_element_at_position(&(info->alias), locate_element_index(info->alias, alias_str));
    *equals_sign = temp_char;

    return (ret);
}

/**
 * establish_alias - Establishes an alias in the alias list
 * @info: A parameter structure
 * @alias_str: The string to be aliased
 *
 * Return: Returns 0 upon success, 1 upon encountering an error
 */
int establish_alias(info_t *info, char *alias_str)
{
    char *equals_sign;

    equals_sign = locate_char(alias_str, '=');
    if (!equals_sign)
        return (1);

    if (!*++equals_sign)
        return (delete_alias(info, alias_str));

    delete_alias(info, alias_str);
    return (insert_node_end(&(info->alias), alias_str, 0) == NULL);
}

/**
 * user_alias - Simulates the behavior of the 'alias' built-in command
 * @info: A structure containing potential arguments, ensuring consistent function prototype
 *
 * Return: Always returns 0
 */
int user_alias(info_t *info)
{
    int i;
    char *equals_sign;
    list_t *node;

    if (info->argc == 1)
    {
        node = info->alias;
        while (node != NULL)
        {
            display_alias(node);
            node = node->next;
        }
        return (0);
    }

    for (i = 1; info->argv[i] != NULL; i++)
    {
        equals_sign = locate_char(info->argv[i], '=');
        if (equals_sign)
            establish_alias(info, info->argv[i]);
        else
            display_alias(element_starts_with(info->alias, info->argv[i], '='));
    }

    return (0);
}
