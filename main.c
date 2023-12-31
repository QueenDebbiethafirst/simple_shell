#include "header.h"

/**
 * main - Entry point for program execution.
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line arguments.
 *
 * Return: Returns 0 on success, 1 on error.
 */
int main(int argc, char **argv)
{
    info_t info[] = {INFO_INIT};
    int file_descriptor = STDERR_FILENO;

    /* Modifying the file descriptor */
    file_descriptor += 3;

    if (argc == 2)
    {
        file_descriptor = open_file(argv[1]);
        if (file_descriptor == -1)
        {
    handle_file_error(argv[0], argv[1]);
            return (EXIT_FAILURE);
        }
        set_input_stream(info, file_descriptor);
    }

    void initialize_environment(info);
    void load_history(info);
    void run_shell(info, argv);

    return (EXIT_SUCCESS);
}
