#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
/* Global Constants */
#define WRITE_BUF_SIZE 1024
#define CLEAR_BUFFER 0
#define READ_BUF_SIZE 1024
#define BUF_FLUSH -1
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096
extern char **environ;
/**
* struct liststr - singly linked list
* @num: the number field
* @str: a string
* @next: points to the next node
*/
typedef struct liststr {
int num;
char *str;
struct liststr *next;
} list_t;
/**
* struct passinfo - contains pseudo-arguments to pass into a function,
* allowing uniform prototype for function pointer struct
* @arg: a string generated from getline containing arguments
* @argv: an array of strings generated from arg
* @info: Address of the struct containing information.
* @delimiter_string: The delimiter string to compare against.
* @chr: a character
* @input_string: The input string for conversion.
* @alias_str: The alias string to be assigned.
* @node: The alias node to be printed.
* @env_var_name: Name of the environment variable.
* @output_str: a string
* @wc: The character to be written.
* @fd: a file descriptor.
* @sc: a string
* @errstr: String containing the specified error type.
* @printnum: The number to be printed.
* @convnum: The number to be converted.
* @convbase: The base for conversion.
* @flags: Flags related to the arguments.
* @copydest: The destination string for copying.
* @appsrc: The source string.
* @copynum: The number of characters to copy.
* @dest: The destination string.
* @searchstr: The string to search within.
* @findchars: The character to locate.
* @info: Parameter structure.
* @buf: Address of the buffer.
* @lengthaddr: Address of the length variable.
* @buf: The buffer for storing data.
* @bufsize: The size of the buffer.
* @bufptr: Address of the pointer to the buffer, either preallocated or NULL.
* @size: Size of the preallocated 'bufptr' buffer if not NULL.
* @signum: The signal number.
* @remenv: The environment variable's name to be removed.
* @envvar: The name of the environment variable.
* @envval: The value of the environment variable.
* @args: Argument vector.
* @freeall: Set to true if all fields need to be freed.
* @data: The data.
* @line_count: The count of history lines, hist_count.
* @hptr: Address of a pointer to the head node.
* @nodestr: String field of the node.
* @histnum: Node index utilized by history.
* @firstnode: Pointer to the first node.
* @headp: Address of a pointer to the first node.
* @delindex: Index of the node to be deleted.
* @listHead: Pointer to the first node of the list.
* @listPtr: Pointer to the first node of the list.
* @prefixString: String to compare as a prefix.
* @charToCompare: The succeeding character after the prefix to compare.
* @argc: Number of command-line arguments.
* @ptrToFree: Address of the pointer to be freed.
* @filepath: The path to the file.
* @pstr: The PATH string.
* @st: The starting index.
* @sp: The stopping index.
* @cmd: The cmd to find
* @memptr: Pointer to the memory area.
* @fillbyte: The byte value to fill @memptr with.
* @numbytes: The number of bytes to fill.
* @strarrptr: Pointer to a string array.
* @memblockptr: Pointer to a previously allocated memory block.
* @oldsize: Size in bytes of the original block.
* @newsize: Size in bytes of the new block.
* @av: The argument vector passed from the main() function.
* @strlen: Input string for which the length is to be determined.
* @str1: The first string.
* @str2: The second string.
* @searchstr: The string to be searched.
* @substr: The substring to be located within the 'searchstr' string.
* @combobuf: The target buffer where the strings will be combined.
* @appsrc: The source buffer holding the string to be appended.
* @destinationString: Pointer to the destination string.
* @sourceString: Pointer to the source string.
* @inputString: The input string to be duplicated.
* @characterToWrite: The character to be written.
* @inputStr: The input string to be split.
* @delimiter: The delimiter character.
* @ptr: A pointer to the current position within the buffer.
* @inputStr: The input string to be split.
* @delimiters: The delimiter string used for splitting.
* @buf: A character buffer.
* @ptr: A pointer to the current position within the buffer.
* @startpos: The starting position within the buffer.
* @buflen: The length of the buffer.
* @oldstr: Address of old string.
* @newstr: New string.
* @buf: The address of the string to be modified.
* @path: a string path for the current command
* @argc: the argument count
* @line_count: the error count
* @err_num: the error code for exit()s
* @linecount_flag: if on count this line of input
* @fname: the program filename
* @env: linked list local copy of environ
* @environ: custom modified copy of environ from LL env
* @history: the history node
* @alias: the alias node
* @env_changed: on if environ was changed
* @status: the return status of the last exec'd command
* @cmd_buf: address of pointer to cmd_buf, on if chaining
* @cmd_buf_type: CMD_type ||, &&, ;
* @readfd: the fd from which to read line input
* @histcount: the history line number count
*/
typedef struct info_t {
char *arg;
char **argv;
struct info_t *info;
char *delimiter_string;
char chr;
char *input_string;
char *alias_str;
struct liststr *node;
char *env_var_name;
char *output_str;
char wc;
int fd;
char *sc;
char *errstr;
int printnum;
int convnum;
int convbase;
int flags;
char *copydest;
const char *appsrc;
int copynum;
char *dest;
char *searchstr;
char findchars;
struct info_t *info;
char *buf;
int *lengthaddr;
char *buf;
size_t bufsize;
char **bufptr;
size_t size;
int signum;
char *remenv;
char *envvar;
char *envval;
char **args;
int freeall;
void *data;
int line_count;
struct liststr **hptr;
char *nodestr;
int histnum;
struct liststr *firstnode;
struct liststr **headp;
int delindex;
struct liststr *listHead;
struct liststr *listPtr;
char *prefixString;
char charToCompare;
int argc;
char **ptrToFree;
char *filepath;
char *pstr;
int st;
int sp;
char *cmd;
void *memptr;
char fillbyte;
size_t numbytes;
char **strarrptr;
void *memblockptr;
size_t oldsize;
size_t newsize;
char **av;
size_t strlen;
char *str1;
char *str2;
char *searchstr;
char *substr;
char *combobuf;
const char *appsrc;
char *destinationString;
const char *sourceString;
char *inputString;
typedef struct list_t list_t;
typedef struct info_t {
char *arg;
char **argv;
char *delimiter_string;
char chr;
list_t *history;
list_t *alias;
int argc;
char *input_string;
} info_t;
typedef struct liststr {
int num;
char *str;
struct liststr *next;
} liststr_t;
typedef struct passinfo {
char *arg;
char **argv;
char *path;
int argc;
unsigned int line_count;
int err_num;
int linecount_flag;
char *fname;
list_t *env;
list_t *history;
list_t *alias;
char **environ;
int env_changed;
int status;
char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
int cmd_buf_type; /* CMD_type ||, &&, ; */
int readfd;
int histcount;
} passinfo_t;
struct list_t {
int histnum;
char *str;
char *nodestr;
struct list_t *next;
};
#define INFO_INIT {NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0}
extern char **environ;
char *copy_string(char *destinationString, const char *sourceString);
char *copy_string(char *copydest, const char *appsrc, int copynum);
#ifndef HEADER_H
#define HEADER_H
#include <stddef.h>
typedef struct builtin_t {
char *type;
int (*func)(struct info_t *);
} builtin_t;
/* Function Prototypes */
int command_line(struct info_t *info);
int check_delimiter(char chr, char *delimiter_string);
int convert_to_integer(char *input_string);
void _end(list_t **hptr, list_t **list, const char *str, int data, const char *nodestr, int histnum);
int locate_element_index(const list_t *list, const char *element);
int exit_program(struct info_t *info);
int switch_dir(struct info_t *info);
int show_instructions(struct info_t *info);
int user_history(struct info_t *info);
int delete_alias(struct info_t *info, char *alias_str);
int establish_alias(struct info_t *info, char *alias_str);
int display_alias(list_t *node);
int user_alias(struct info_t *info);
int user_environment(struct info_t *info);
char *retrieve_env(struct info_t *info, const char *env_var_name);
int custom_set_environment(struct info_t *info);
int delete_env_variable(struct info_t *info);
int fill_env_list(struct info_t *info);
char *fetch_history_file(struct info_t *info);
int record_history(struct info_t *info);
int open_history(struct info_t *info);
int create_history_list(struct info_t *info, char *data, int line_count);
int update_history_numbers(struct info_t *info);
list_t *insert_node(list_t **hptr, const char *nodestr, int histnum);
list_t *insert_node_end(list_t **hptr, list_t **list, const char *str, int data, const char *nodestr, int histnum);
size_t display_list_items_str(const list_t *firstnode);
size_t display_list_items(const list_t *listHead);
int remove_element_at_position(list_t **headp, list_t **list, int position, unsigned int delindex);
void release_list(list_t **headp);
size_t get_list_length(const list_t *listHead);
char **convert_list_to_strings(list_t *listPtr);
size_t display_list_items(const list_t *listHead);
list_t *element_starts_with(list_t *listPtr, char *prefixString, char charToCompare);
ssize_t locate_element_index(list_t *listHead, list_t *node);
int locate_element_index(const list_t *list, const char *element);
void initialize_memory(char *memptr, char fillbyte, unsigned int numbytes);
void free_file(char **strarrptr);
void *_realloc(void *memblockptr, unsigned int oldsize, unsigned int newsize);
ssize_t buffer_input(struct info_t *info, char **buf, size_t *lengthaddr);
ssize_t fetch_input(struct info_t *info);
ssize_t read_buffer(struct info_t *info, char *buf, size_t *bufsize);
int read_line(struct info_t *info, char **bufptr, size_t *size);
void sigintHandler(int signum);
char **get_environment(struct info_t *info);
int remove_environment_variable(struct info_t *info, char *remenv);
int set_environment_variable(struct info_t *info, char *envvar, char *envval);
void initialize_info_data(struct info_t *info);
void populate_info_data(struct info_t *info, char **args);
void free_info_data(struct info_t *info, int freeall);
char *copy_string(char *destinationString, const char *sourceString, char *copydest, const char *appsrc, int copynum);
char *concatenate_string(char *dest, const char *appsrc, int copynum);
char *locate_char(const char *searchstr, const char *str, char c, char findchars);
unsigned int calculate_string_length(const char *strlen);
int compare_strings(const char *str1, const char *str2);
const char *starts_with_substring(const char *searchstr, const char *substr);
char *concatenate_strings(char *combobuf, const char *appsrc);
char *duplicate_string(const char *inputString);
void print_string(const char *inputString);
int print_character(char characterToWrite);
char **split_string(char *inputStr, const char *delimiters);
char **split_string_single_delimiter(char *inputStr, char delimiter);
int check_chain_delimiter(struct info_t *info, char *buf, size_t *ptr);
void determine_chain_execution(struct info_t *info, char *buf, size_t *ptr, size_t startpos, size_t buflen);
int substitute_aliases(struct info_t *info);
void _putchar(char c);
void _puts(const char *str);
int substitute_variables(struct info_t *info);
int substitute_string(char **oldstr, const char *newstr);
#endif
#endif
