#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <signal.h>
#include <stddef.h>

/* Constants */
#define STDERR_FILENO 2
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define CLEAR_BUFFER '\0'
#define STDIN_FILENO 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3
#define WRITE_BUFFER_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define MAX_STRING_LENGTH 100
#define HIST_FILE "history.txt"
#define HIST_MAX 100
#define READ_BUFFER_SIZE 1024
#define F_OK 0
#define X_OK 1

/* External Variables */
extern char **environ;
extern list_t *Info_env_data;
extern int execution_status;
extern int err_code;

/**
 * str_to_int_with_error_handling - Converts a string to an integer with error handling.
 * @str: The input string to be converted.
 *
 * Return: The integer value if successful, -1 on error.
 */
int str_to_int_with_error_handling(char *str);

/**
 * output_error - Outputs an error message to the standard error stream.
 * @info: A structure holding potential arguments and maintaining a consistent function prototype.
 * @msg: The error message to be printed.
 */
void output_error(info_t *info, char *msg);

/**
 * print_char - Prints a character to the standard output.
 * @c: The character to be printed.
 */
void print_char(char c);

/**
 * retrieve_env - Retrieves an environment variable value.
 * @info: A structure holding potential arguments and maintaining a consistent function prototype.
 * @prefix: The prefix of the environment variable.
 *
 * Return: A pointer to the environment variable value or NULL if not found.
 */
char* retrieve_env(info_t *info, char *prefix);

/**
 * _puts - Prints a string to the standard output.
 * @str: The string to be printed.
 */
void _puts(char *str);

/**
 * _strcmp - Compares two strings.
 * @s1: The first string.
 * @s2: The second string.
 *
 * Return: 0 if the strings are equal, a negative value if s1 < s2, a positive value if s1 > s2.
 */
int _strcmp(char *s1, char *s2);

/**
 * exit_program - Exits the program with an optional error code.
 * @info: A structure holding potential arguments and maintaining a consistent function prototype.
 *
 * Return: An exit code (-2, -1, or 0).
 */
int exit_program(info_t *info);

/**
 * switch_dir - Changes the current working directory.
 * @info: A structure holding potential arguments and maintaining a consistent function prototype.
 *
 * Return: 0 on success, 1 on failure.
 */
int switch_dir(info_t *info);

/**
 * show_instructions - Displays program instructions.
 * @info: A structure holding potential arguments and maintaining a consistent function prototype.
 *
 * Return: Always returns 0.
 */
int show_instructions(info_t *info);

/* Struct definition for singly linked list */
typedef struct list_s
{
    char *nodestr;
    int histnum;
char *data;
    int num;
    struct list_s *next;
char *str;
} list_t;

/* Define the info_t structure */
typedef struct {
    char **arguments;
    char **arg_vector;
    char *executable_path;
    char *program_name;
    int arg_count;
} info_t;

/*Struct definition */
typedef struct info_s
{
list_t *history;
    int hist_count;
    char **argv;
int input_stream;
    int linecount_flag;
    int histcount;
    int cmd_buf_type;
    char **arg;
} info_t;

typedef struct info {
    int argc;
    char **argv;
    int cmd_buf_type;
    char *alias;
    char *env_data;
char *path;
    char **argv;
    int linecount_flag;
    int line_count;
    char *arg;
} info_t;

typedef struct {
    int id;
    char name[MAX_STRING_LENGTH];
} Person;

/* Function Declarations */
void reset_data(info_t *info);
void print_char(char c);
ssize_t fetch_input(info_t *info);
void save_data(info_t *info, char **av);
int locate_builtin(info_t *info);
void find_command(info_t *info);
int command_line(info_t *info);
void deallocate_info(info_t *info, int flag);
void record_history(info_t *info);
void locate_and_execute_command(info_t *info);
void locate_command(info_t *info);
char *retrieve_env(info_t *info, const char *env_var);
int main(int argc, char **argv);
int open_file(const char *filename);
void handle_file_error(const char *program_name, const char *filename);
void set_input_stream(info_t *info, int file_descriptor);
void initialize_environment(info_t *info);
void load_history(info_t *info);
void run_shell(info_t *info, char **argv);
char *initialize_memory(char *memptr, char fillbyte, unsigned int numbytes);
void free_file(char **strarrptr);
void *_realloc(void *memblockptr, unsigned int oldsize, unsigned int newsize);
void someFunction(int param);
void output_error(char *output_str);
int write_char(char wc);
int write_fd(char wc, int fd);
int print_fd(char *output_str, int fd);
int command_line(info_t *info);
int check_delimiter(char chr, char *delimiter_string);
int char_is_alpha(int chr);
int convert_to_integer(char *input_string);
int calculate_string_length(const char *str);
int compare_strings(const char *str1, const char *str2);
char *starts_with_substring(const char *searchstr, const char *substr);
char *concatenate_strings(char *dest, const char *src);
int user_environment(info_t *info);
char *retrieve_env(info_t *info, const char *env_var_name);
int custom_set_environment(info_t *info);
int delete_env_variable(info_t *info);
int fill_env_list(info_t *info);
char **split_string(char *inputStr, char *delimiters);
char **split_string_single_delimiter(char *inputStr, char delimiter);
bool is_delimiter(char character, char *delimiters);
char *copy_string(char *destinationString, const char *sourceString);
char *duplicate_string(const char *inputString);
void print_string(char *inputString);
int print_character(char characterToWrite);
int check_chain_delimiter(info_t *info, char *buf, size_t *ptr);
void determine_chain_execution(info_t *info, char *buf, size_t *ptr, size_t startpos, size_t buflen);
int substitute_aliases(info_t *info);
int substitute_variables(info_t *info);
int substitute_string(char **oldstr, char *newstr);


/* Function prototypes for singly linked list */
int calculateListLength(list_t *head);
void handleError(const char *errorMessage);
size_t get_list_length(const list_t *listHead);
char **convert_list_to_strings(list_t *listPtr);
size_t display_list_items(const list_t *listHead);
list_t *element_starts_with(list_t *listPtr, char *prefixString, char charToCompare);
ssize_t locate_element_index(list_t *listHead, list_t *node);

/* Function prototypes for info_t structure */
void initialize_info_data(info_t *info);
void populate_info_data(info_t *info, char **args);
void free_info_data(info_t *info, int freeall);

/* Function prototypes for the third section */
void signal_handler(int signal);
int main();
void initialize_info_data(info_t *info);
void populate_info_data(info_t *info, char **args);
void free_info_data(info_t *info, int freeall);
ssize_t buffer_input(info_t *info, char **buf, size_t *lengthaddr);
ssize_t fetch_input(info_t *info);
ssize_t read_buffer(info_t *info, char *buf, size_t *bufsize);
int read_line(info_t *info, char **bufptr, size_t *size);

/* Function prototypes for the fourth section */
int check_command(info_t *info, char *filepath);
char *duplicate_characters(const char *pstr, int st, int sp);
char *locate_path(info_t *info, const char *pstr, const char *cmd);
void sigintHandler(int signum);
int str_to_int_with_error_handling(char *sc);
void output_error(info_t *info, char *errstr);
int print_debug(int printnum, int fd);
char *parse_number(long int convnum, int convbase, int flags);
void eliminate_comments(char *buf);
char *fetch_history_file(info_t *info);
int record_history(info_t *info);
int open_history(info_t *info);
void remove_element_at_position(list_t **head, int position);
void insert_node_end(list_t **head, char *data, int line_count);
int read_history(info_t *info);
int create_history_list(info_t *info, char *data, int line_count);
int update_history_numbers(info_t *info);
char* concatenate_string(const char* str1, const char* str2);
int locate_char(const char* str, char ch);
char *copy_string(char *copydest, const char *appsrc, int copynum);
char *concatenate_string(char *dest, const char *appsrc, int copynum);
char *locate_char(const char *searchstr, char findchars);

#endif 
