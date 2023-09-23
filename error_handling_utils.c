#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include "list.h"


#define MAX_STRING_LENGTH 100

typedef struct 
{
    int id;
    char name[MAX_STRING_LENGTH];
} Person;

void printPerson(Person *person) 
{
    printf("ID: %d\n", person->id);
    printf("Name: %s\n", person->name);
}

int main() 
{
    Person person;
    person.id = 1;
    snprintf(person.name, MAX_STRING_LENGTH, "John Doe");

    printPerson(&person);

    return (0);
}

#include <stdio.h>
#include <limits.h>

/**
 * str_to_int_with_error_handling - Converts a string to an integer.
 * @sc: The string to be converted.
 *
 * Return: Returns 0 if there are no numbers in the string, the converted number otherwise, and -1 in case of an error.
 */
int str_to_int_with_error_handling(char *sc)
{
    int i = 0;
    unsigned long int result = 0;

    if (*sc == '+')
        sc++;

    for (i = 0; sc[i] != '\0'; i++)
    {
        if (sc[i] >= '0' && sc[i] <= '9')
        {
            result *= 10;
            result += (sc[i] - '0');
            if (result > INT_MAX)
                return (-1);
        }
        else
        {
            return (-1);
        }
    }
    return (result);
}

/**
 * output_error - Outputs an error message.
 * @info: The structure containing parameter and return information.
 * @errstr: String containing the specified error type.
 *
 * Return: Returns 0 if successful, indicating no numbers in the string; otherwise, returns -1 on error.
 */
void output_error(info_t *info, char *errstr)
{
    output_error(info->fname);
    output_error(": ");
    print_debug(info->line_count, STDERR_FILENO);
    output_error(": ");
    output_error(info->argv[0]);
    output_error(": ");
    output_error(errstr);
}

/**
 * print_debug - Prints a decimal (integer) number in base 10.
 * @printnum: The number to be printed.
 * @fd: The file descriptor for writing.
 *
 * Return: The count of characters that were printed.
 */
int print_debug(int printnum, int fd)
{
    int (*__putchar)(char) = _putchar;
    int i, count = 0;
    unsigned int _abs_, current;

    if (fd == STDERR_FILENO)
        __putchar = print_char;

    if (printnum < 0)
    {
        _abs_ = -printnum;
        __putchar('-');
        count++;
    }
    else
    {
        _abs_ = printnum;
    }

    current = _abs_;

    for (i = 1000000000; i > 1; i /= 10)
    {
        if (_abs_ / i)
        {
            __putchar('0' + current / i);
            count++;
        }
        current %= i;
    }

    __putchar('0' + current);
    count++;

    return (count);
}

/**
 * parse_number - Converts a number to a string representation.
 * @convnum: The number to be converted.
 * @convbase: The base for conversion.
 * @flags: Flags related to the arguments.
 *
 * Return: Returns a string as a result of the conversion.
 */
char *parse_number(long int convnum, int convbase, int flags)
{
    static char buffer[50];
    char sign = 0;
    char *charptr;
    unsigned long n = convnum;

    if (!(flags & CONVERT_UNSIGNED) && convnum < 0)
    {
        n = -convnum;
        sign = '-';
    }

    char *array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
    charptr = &buffer[49];
    *charptr = '\0';

    do {
        *--charptr = array[n % convbase];
        n /= convbase;
    }
      while (n != 0);

    if (sign)
        *--charptr = sign;

    return (charptr);
}

/**
 * eliminate_comments - Replaces the first occurrence of '#' with '\0' in the string.
 * @buf: The address of the string to be modified.
 *
 * Return: None.
 */
void eliminate_comments(char *buf)
{
    int i;

    for (i = 0; buf[i] != '\0'; i++)
    {
        if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
        {
            buf[i] = '\0';
            break;
        }
    }
}
