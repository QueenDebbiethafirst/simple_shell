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

#define READ_BUFFER_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define CLEAR_BUFFER -1 

#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3 

#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2 

#define USE_READ_LINE 0
#define USE_STRTOK 0 


/* Global Constants */
#define WRITE_BUF_SIZE 1024 // You can adjust this value as needed
#define HIST_FILE "event_log.c,fetch_history_file" // Replace with the actual history file name

/* Data Structures */
typedef struct info_t {
    // Define your info_t structure here based on the information provided
} info_t;

typedef struct list_t {
    int histnum;           // Node index utilized by history
    char *nodestr;         // String field of the node
    struct list_t *next;   // Pointer to the next node
} list_t;

/* Function Prototypes */
int command_line(info_t *info);
int check_delimiter(char chr, char *delimiter_string);
int char_is_alpha(int chr);
int convert_to_integer(char *input_string);
int exit_program(info_t *info);
int switch_dir(info_t *info);
int show_instructions(info_t *info);
int user_history(info_t *info);
int delete_alias(info_t *info, char *alias_str);
int establish_alias(info_t *info, char *alias_str);
int display_alias(list_t *node);
int user_alias(info_t *info);
int user_environment(info_t *info);
char *retrieve_env(info_t *info, const char *env_var_name);
int custom_set_environment(info_t *info);
int delete_env_variable(info_t *info);
int fill_env_list(info_t *info);
char *fetch_history_file(info_t *info);
int record_history(info_t *info);
int open_history(info_t *info);
int create_history_list(info_t *info, char *data, int line_count);
int update_history_numbers(info_t *info);
list_t *insert_node(list_t **hptr, const char *nodestr, int histnum);
list_t *insert_node_end(list_t **hptr, const char *nodestr, int histnum);
size_t display_list_items_str(const list_t *firstnode);
int remove_element_at_position(list_t **headp, unsigned int delindex);
void release_list(list_t **headp);
size_t get_list_length(const list_t *listHead);
char **convert_list_to_strings(list_t *listPtr);
size_t display_list_items(const list_t *listHead);
list_t *element_starts_with(list_t *listPtr, char *prefixString, char charToCompare);
ssize_t locate_element_index(list_t *listHead, list_t *node);
void initialize_memory(char *memptr, char fillbyte, unsigned int numbytes);
void free_file(char **strarrptr);
void *_realloc(void *memblockptr, unsigned int oldsize, unsigned int newsize);
ssize_t buffer_input(info_t *info, char **buf, size_t *lengthaddr);
ssize_t fetch_input(info_t *info);
ssize_t read_buffer(info_t *info, char *buf, size_t *bufsize);
int read_line(info_t *info, char **bufptr, size_t *size);
void sigintHandler(int signum);
char **get_environment(info_t *info);
int remove_environment_variable(info_t *info, char *remenv);
int set_environment_variable(info_t *info, char *envvar, char *envval);
void initialize_info_data(info_t *info);
void populate_info_data(info_t *info, char **args);
void free_info_data(info_t *info, int freeall);
char *copy_string(char *copydest, const char *appsrc, int copynum);
char *concatenate_string(char *dest, const char *appsrc, int copynum);
char *locate_char(const char *searchstr, char findchars);
unsigned int calculate_string_length(const char *strlen);
int compare_strings(const char *str1, const char *str2);
const char *starts_with_substring(const char *searchstr, const char *substr);
char *concatenate_strings(char *combobuf, const char *appsrc);
char *copy_string(char *destinationString, const char *sourceString);
char *duplicate_string(const char *inputString);
void print_string(const char *inputString);
int print_character(char characterToWrite);
char **split_string(char *inputStr, const char *delimiters);
char **split_string_single_delimiter(char *inputStr, char delimiter);
int check_chain_delimiter(info_t *info, char *buf, size_t *ptr);
void determine_chain_execution(info_t *info, char *buf, size_t *ptr, size_t startpos, size_t buflen);
int substitute_aliases(info_t *info);
int substitute_variables(info_t *info);
int substitute_string(char **oldstr, const char *newstr);

#endif 
 
