#include "header.h"
#include <stdio.h>

/**
 * calculate_string_length - Calculates and returns the length of a string.
 *
 * @str: Input string for which the length is to be determined.
 *
 * Return: An integer indicating the length of the string.
 */
int calculate_string_length(const char *str)
{
    int length = 0;
    
    if (!str)
        return 0;
    
    while (str[length] != '\0')
        length++;
    
    return length;
}

/**
 * compare_strings - Compares two strings lexicographically.
 *
 * @str1: The first string.
 * @str2: The second string.
 *
 * Return: Negative if str1 < str2, positive if str1 > str2, zero if str1 == str2.
 */
int compare_strings(const char *str1, const char *str2)
{
    while (*str1 && *str2)
    {
        if (*str1 != *str2)
            return (*str1 - *str2);
        
        str1++;
        str2++;
    }
    
    return 0;
}

/**
 * starts_with_substring - Determines whether the 'substr' string starts with the 'searchstr' string.
 *
 * @searchstr: The string to be searched.
 * @substr: The substring to be located within the 'searchstr' string.
 *
 * Return: A pointer to the character following the matched substring in 'searchstr', or NULL if no match is found.
 */
char *starts_with_substring(const char *searchstr, const char *substr)
{
    while (*substr)
    {
        if (*substr++ != *searchstr++)
            return NULL;
    }
    
    return (char *)searchstr;
}

/**
 * concatenate_strings - Combines two strings.
 *
 * @dest: The target buffer where the strings will be combined.
 * @src: The source buffer holding the string to be appended.
 *
 * Return: A pointer to the destination buffer after concatenation.
 */
char *concatenate_strings(char *dest, const char *src)
{
    char *result = dest;
    
    while (*dest)
        dest++;
    
    while (*src)
        *dest++ = *src++;
    
    *dest = '\0';
    
    return result;
}
