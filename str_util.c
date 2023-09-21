#include "header.h"
/**
 * calculate_string_length - Calculates and returns the length of a string.
 *
 * @strlen: Input string for which the length is to be determined.
 *
 * Return: An integer indicating the length of the string.
 */
int calculate_string_length(char *strlen)
{
 int length = 0;
 if (!strlen)
 return (0);
 while (*strlen++)
 length++;
 return (length);
}
/**
 * compare_strings - Compares two strings lexicographically.
 *
 * @str1: The first string.
 * @str2: The second string.
 *
 * Return: Negative if str1 < str2, positive if str1 > str2, zero if str1 == str2.
 */
int compare_strings(char *str1, char *str2)
{
 while (*str1 && *str2)
 {
 if (*str1 != *str2)
 return (*str1 - *str2);
 str1++;
 str2++;
 }
 if (*str1 == *str2)
 return (0);
 else
 return (*str1 < *str2 ? -1 : 1);
}
/**
 * starts_with_substring - Determines whether the 'substr' string starts with the 'searchstr' string.
 *
 * @searchstr: The string to be searched.
 * @substr: The substring to be located within the 'searchstr' string.
 *
 * Return: The memory address of the character following the matched substring in 'searchstr', or NULL if no match is found.
 */
char *starts_with_substring(const char *searchstr, const char *substr)
{
 while (*substr)
 {
 if (*substr++ != *searchstr++)
 return (NULL);
 }
 return ((char *)searchstr);
}
/**
 * concatenate_strings - Combines two strings.
 *
 * @combobuf: The target buffer where the strings will be combined.
 * @appsrc: The source buffer holding the string to be appended.
 *
 * Return: A pointer to the destination buffer after concatenation.
 */
char *concatenate_strings(char *combobuf, char *appsrc)
{
 char *result = combobuf;
 while (*combobuf)
 combobuf++;
 while (*appsrc)
 *combobuf++ = *appsrc++;
 *combobuf = *appsrc;
 return (result);
}
