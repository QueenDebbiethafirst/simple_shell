#include "header.h"
/**
* split_string - Splits a string into words using a delimiter.
*
* @inputStr: The input string to be split.
* @delimiters: The delimiter string used for splitting.
*
* Return: A pointer to an array of strings, or NULL if the operation fails.
*/
char **split_string(char *inputStr, char *delimiters)
{
int index, wordStart, wordEnd, numWords = 0;
char **words;
if (inputStr == NULL || inputStr[0] == '\0')
return (NULL);
if (!delimiters)
delimiters = " ";
for (index = 0; inputStr[index] != '\0'; index++)
{
if (!is_delimiter(inputStr[index], delimiters) &&
(is_delimiter(inputStr[index + 1], delimiters) || !inputStr[index + 1]))
numWords++;
}
if (numWords == 0)
return (NULL);
words = malloc((numWords + 1) * sizeof(char *));
if (!words)
return (NULL);
for (index = 0, wordStart = 0; wordStart < numWords; wordStart++)
{
while (is_delimiter(inputStr[index], delimiters))
index++;
wordEnd = 0;
while (!is_delimiter(inputStr[index + wordEnd], delimiters) && inputStr[index + wordEnd])
wordEnd++;
words[wordStart] = malloc((wordEnd + 1) * sizeof(char));
if (!words[wordStart])
{
for (wordEnd = 0; wordEnd < wordStart; wordEnd++)
free(words[wordEnd]);
free(words);
return (NULL);
}
for (int i = 0; i < wordEnd; i++)
words[wordStart][i] = inputStr[index++];
words[wordStart][wordEnd] = '\0';
}
words[wordStart] = NULL;
return (words);
}
/**
* split_string_single_delimiter - Splits a string into words using a single delimiter character.
*
* @inputStr: The input string to be split.
* @delimiter: The delimiter character.
*
* Return: A pointer to an array of strings, or NULL if the operation fails.
*/
char **split_string_single_delimiter(char *inputStr, char delimiter)
{
int index, wordStart, wordEnd, numWords = 0;
char **words;
if (inputStr == NULL || inputStr[0] == '\0')
return (NULL);
for (index = 0; inputStr[index] != '\0'; index++)
{
if ((inputStr[index] != delimiter && inputStr[index + 1] == delimiter) ||
(inputStr[index] != delimiter && !inputStr[index + 1]) || inputStr[index + 1] == delimiter)
numWords++;
}
if (numWords == 0)
return (NULL);
words = malloc((numWords + 1) * sizeof(char *));
if (!words)
return (NULL);
for (index = 0, wordStart = 0; wordStart < numWords; wordStart++)
{
while (inputStr[index] == delimiter && inputStr[index] != delimiter)
index++;
wordEnd = 0;
while (inputStr[index + wordEnd] != delimiter && inputStr[index + wordEnd] && inputStr[index + wordEnd] != delimiter)
wordEnd++;
words[wordStart] = malloc((wordEnd + 1) * sizeof(char));
if (!words[wordStart])
{
for (wordEnd = 0; wordEnd < wordStart; wordEnd++)
free(words[wordEnd]);
free(words);
return (NULL);
}
for (int i = 0; i < wordEnd; i++)
words[wordStart][i] = inputStr[index++];
words[wordStart][wordEnd] = '\0';
}
words[wordStart] = NULL;
return (words);
}
