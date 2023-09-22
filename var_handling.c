#include "header.h"

/**
 * check_chain_delimiter - Checks if the current character in the buffer serves as a chain delimiter.
 *
 * @info: A structure containing parameters for the function.
 * @buf: The character buffer containing the data.
 * @ptr: A pointer to the current position within the buffer.
 *
 * Return: 1 if the character is a chain delimiter, 0 otherwise.
 */
int check_chain_delimiter(info_t *info, char *buf, size_t *ptr)
{
    size_t startpos = *ptr;

    if (buf[startpos] == '|' && buf[startpos + 1] == '|')
    {
        buf[startpos] = 0;
        startpos++;
        info->cmd_buf_type = CMD_OR;
    }
    else if (buf[startpos] == '&' && buf[startpos + 1] == '&')
    {
        buf[startpos] = 0;
        startpos++;
        info->cmd_buf_type = CMD_AND;
    }
    else if (buf[startpos] == ';') /* found end of this command */
    {
        buf[startpos] = 0; /* replace semicolon with null */
        info->cmd_buf_type = CMD_CHAIN;
    }
    else
    {
        return (0);
    }

    *ptr = startpos;
    return (1);
}

/**
 * determine_chain_execution - Determines whether the chaining should proceed based on the previous status.
 *
 * @info: A struct containing parameters.
 * @buf: A character buffer.
 * @ptr: A pointer to the current position within the buffer.
 * @startpos: The starting position within the buffer.
 * @buflen: The length of the buffer.
 *
 * Return: This function returns void.
 */
void determine_chain_execution(info_t *info, char *buf, size_t *ptr, size_t startpos, size_t buflen)
{
    size_t currentpos = *ptr;

    if (info->cmd_buf_type == CMD_AND)
    {
        if (execution_status)
        {
            buf[startpos] = 0;
            currentpos = buflen;
        }
    }

    if (info->cmd_buf_type == CMD_OR)
    {
        if (!execution_status)
        {
            buf[startpos] = 0;
            currentpos = buflen;
        }
    }

    *ptr = currentpos;
}

/**
 * substitute_aliases - Replaces aliases within the tokenized string.
 *
 * @info: A struct containing necessary parameters.
 *
 * Return: 1 if at least one alias was replaced, 0 otherwise.
 */
int substitute_aliases(info_t *info)
{
    list_t *node;
    char *ptr;

    node = element_starts_with(info->alias, info->argv[0], '=');
    if (!node)
    {
        return (0);
    }

    free(info->argv[0]);
    ptr = locate_char(node->str, '=');
    if (!ptr)
    {
        return (0);
    }

    ptr = _strdup(ptr + 1);
    if (!ptr)
    {
        return (0);
    }

    info->argv[0] = ptr;

    return (1);
}

/**
 * substitute_variables - Substitutes variables within a tokenized string.
 *
 * @info: A struct containing parameters.
 *
 * Return: The function returns 1 if the variables are successfully replaced, and 0 if no replacements are made.
 */
int substitute_variables(info_t *info)
{
    int i = 0;
    list_t *node;

    for (i = 0; info->argv[i]; i++)
    {
        if (info->argv[i][0] != '$' || !info->argv[i][1])
        {
            continue;
        }

        if (!_strcmp(info->argv[i], "$?"))
        {
            substitute_string(&(info->argv[i]), _strdup(parse_number(execution_status, 10, 0)));
            continue;
        }

        if (!_strcmp(info->argv[i], "$$"))
        {
            substitute_string(&(info->argv[i]), _strdup(parse_number(getpid(), 10, 0)));
            continue;
        }

        node = element_starts_with(info->env_data, &info->argv[i][1], '=');
        if (node)
        {
            substitute_string(&(info->argv[i]), _strdup(locate_char(node->str, '=') + 1));
            continue;
        }

        substitute_string(&info->argv[i], _strdup(""));
    }

    return (0);
}

/**
 * substitute_string - Replaces string.
 *
 * @oldstr: Address of old string.
 * @newstr: New string.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int substitute_string(char **oldstr, char *newstr)
{
    if (*oldstr)
    {
        free(*oldstr);
    }

    *oldstr = newstr;

    return (1);
}
