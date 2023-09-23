#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "list.h"

#define WRITE_BUFFER_SIZE 1024
#define CLEAR_BUFFER '\0'

/**
 * copy_string - Copies a string.
 *
 * @destinationString: Pointer to the destination string.
 * @sourceString: Pointer to the source string.
 *
 * Return: Pointer to the destination string.
 */
char *copy_string(char *destinationString, const char *sourceString)
{
    int index = 0;

    if (destinationString == sourceString || sourceString == NULL)
        return destinationString;

    while (sourceString[index])
    {
        destinationString[index] = sourceString[index];
        index++;
    }
    destinationString[index] = '\0';

    return (destinationString);
}

/**
 * duplicate_string - Creates a duplicate of a string.
 *
 * @inputString: The input string to be duplicated.
 *
 * Return: A pointer to the newly duplicated string.
 */
char *duplicate_string(const char *inputString)
{
    int length = 0;
    char *duplicate;

    if (inputString == NULL)
        return (NULL);

    while (inputString[length])
        length++;

    duplicate = malloc(sizeof(char) * (length + 1));
    if (!duplicate)
        return (NULL);

    for (int i = 0; i <= length; i++)
        duplicate[i] = inputString[i];

    return (duplicate);
}

/**
 * print_string - Displays the provided string.
 *
 * @inputString: Input string to be printed.
 *
 * Return: None.
 */
void print_string(char *inputString)
{
    int index = 0;

    if (!inputString)
        return;

    while (inputString[index] != '\0')
    {
        print_character(inputString[index]);
        index++;
    }
}

/**
 * print_character - Writes a single character to the standard output (stdout).
 *
 * @characterToWrite: The character to be written.
 *
 * Return: Returns 1 upon success.
 *         If an error occurs, it returns -1 and sets the appropriate errno.
 */
int print_character(char characterToWrite)
{
    static int currentIndex = 0;
    static char buffer[WRITE_BUFFER_SIZE];

    if (characterToWrite == CLEAR_BUFFER || currentIndex >= WRITE_BUFFER_SIZE)
    {
        write(1, buffer, currentIndex);
        currentIndex = 0;
    }

    if (characterToWrite != CLEAR_BUFFER)
        buffer[currentIndex++] = characterToWrite;

    return (1);
}
