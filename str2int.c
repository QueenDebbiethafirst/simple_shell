#include "header.h"

/**
 * command_line - Checks if the shell is in command line mode.
 * @info: Address of the struct containing information.
 *
 * Return: 1 if the shell is in command line mode, 0 otherwise.
 */
int command_line(info_t *info)
{
    int isCommandLine = isatty(STDIN_FILENO) && info->input_stream <= 2;
    return (isCommandLine);
}

/**
 * check_delimiter - Determines whether a character is a delimiter.
 * @chr: The character to be checked.
 * @delimiter_string: The delimiter string to compare against.
 *
 * Return: 1 if the condition is true, 0 if false.
 */
int check_delimiter(char chr, char *delimiter_string)
{
    while (*delimiter_string != '\0')
    {
        if (*delimiter_string == chr)
        {
            return (1);
        }
        delimiter_string++;
    }
    return (0);
}

/**
 * char_is_alpha - Verifies if a character is an alphabet letter.
 * @chr: The character to be examined.
 *
 * Return: 1 if 'chr' is an alphabet letter, 0 otherwise.
 */
int char_is_alpha(int chr)
{
    int isAlpha = (chr >= 'a' && chr <= 'z') || (chr >= 'A' && chr <= 'Z');
    return (isAlpha);
}

/**
 * convert_to_integer - Transforms a string into an integer.
 * @input_string: The input string for conversion.
 *
 * Return: 0 if there are no numbers in the string; otherwise, returns the converted number.
 */
int convert_to_integer(char *input_string)
{
    int index = 0;
    int sign = 1;
    int flag = 0;
    int converted_number = 0;
    unsigned int result = 0;

    while (input_string[index] != '\0' && flag != 2)
    {
        if (input_string[index] == '-')
        {
            sign *= -1;
        }
        if (input_string[index] >= '0' && input_string[index] <= '9')
        {
            flag = 1;
            result *= 10;
            result += (input_string[index] - '0');
        }
        else if (flag == 1)
        {
            flag = 2;
        }
        index++;
    }

    if (sign == -1)
    {
        converted_number = -result;
    }
    else
    {
        converted_number = result;
    }

    return (converted_number);
}
