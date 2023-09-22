#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function to concatenate two strings */
char* concatenate_string(const char* str1, const char* str2) 
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    char* result = malloc((len1 + len2 + 1) * sizeof(char));
    if (result == NULL) 
    {
        printf("Memory allocation failed\n");
        return (NULL);
    }
    strcpy(result, str1);
    strcat(result, str2);
    return (result);
}

/* Function to locate a character in a string */
int locate_char(const char* str, char ch) 
{
    int len = strlen(str);
    for (int i = 0; i < len; i++) 
    {
        if (str[i] == ch) 
        {
            return (i);
        }
    }
    return (-1);
}

int main() 
{
    const char* str1 = "Hello";
    const char* str2 = "World";
    char* concatenated = concatenate_string(str1, str2);
    printf("Concatenated string: %s\n", concatenated);
    free(concatenated);
    
    const char* str = "Hello, World!";
    char ch = 'o';
    int index = locate_char(str, ch);
    if (index != -1) 
    {
        printf("Character '%c' found at index %d\n", ch, index);
    } 
    else 
    {
        printf("Character '%c' not found in the string\n", ch);
    }
    
    return (0);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * copy_string - Duplicates a string.
 * @copydest: The destination string for copying.
 * @appsrc: The source string.
 * @copynum: The number of characters to copy.
 *
 * Return: The resulting duplicated string.
 */
char *copy_string(char *copydest, const char *appsrc, int copynum)
{
    int i;
    char *result = malloc((copynum + 1) * sizeof(char));
    if (result == NULL)
    {
        printf("Memory allocation failed\n");
        return (NULL);
    }
    for (i = 0; i < copynum && appsrc[i] != '\0'; i++)
    {
        result[i] = appsrc[i];
    }
    result[i] = '\0';
    strcpy(copydest, result);
    free(result);
    return (copydest);
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
    char *result = malloc((strlen(dest) + copynum + 1) * sizeof(char));
    if (result == NULL)
    {
        printf("Memory allocation failed\n");
        return (NULL);
    }
    strcpy(result, dest);
    for (i = strlen(dest), j = 0; j < copynum && appsrc[j] != '\0'; i++, j++)
    {
        result[i] = appsrc[j];
    }
    result[i] = '\0';
    strcpy(dest, result);
    free(result);
    return (dest);
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
    while (*searchstr != '\0')
    {
        if (*searchstr == findchars)
        {
            return ((char *)searchstr);
        }
        searchstr++;
    }
    return (NULL);
}
