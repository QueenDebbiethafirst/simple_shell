nclude <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Definitions from the first header file */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
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

typedef struct liststr {
	    int num;
	        char *str;
		    struct liststr *next;
} list_t;

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
								    char **cmd_buf;
								        int cmd_buf_type;
									    int readfd;
									        int histcount;
} info_t;

typedef struct builtin {
	    char *type;
	        int (*func)(info_t *);
} builtin_table;

/* Definitions from the second header file */
#define CLEAR_BUFFER 0x1A
#define USE_READ_LINE 0

typedef struct info_t {
	    char *arguments;
	        char **arg_vector;
		    char *executable_path;
		        int arg_count;
			    char *program_name;
			        list_t *history;
				    list_t *environment_data;
				        list_t *alias_data;
					    char **environment_strings;
					        int input_stream;
						    char **command_buffer;
						        int hist_count;
							    int env_data_changed;
							        int linecount_flag;
} info_t;

typedef struct list_s {
	    char *nodestr;
	        int histnum;
		    struct list_s *next;
} list_t;

/* Function declarations from the first header file */
size_t get_list_length(const list_t *listHead);
char **convert_list_to_strings(list_t *listPtr);
size_t display_list_items(const list_t *listHead);
list_t *element_starts_with(list_t *listPtr, char *prefixString, char charToCompare);
ssize_t locate_element_index(list_t *listHead, list_t *node);
int free_buffer(void **ptrToFree);
int main(int argc, char **argv);
char *initialize_memory(char *memptr, char fillbyte, unsigned int numbytes);
void free_file(char **strarrptr);
void *_realloc(void *memblockptr, unsigned int oldsize, unsigned int newsize);
int check_command(info_t *info, char *filepath);
char *duplicate_characters(char *pstr, int st, int sp);
char *locate_path(info_t *info, char *pstr, char *cmd);
int command_line(info_t *info);
int check_delimiter(char chr, char *delimiter_string);
int char_is_alpha(int chr);
int convert_to_integer(char *input_string);

/* Function declarations from the second header file */
char *copy_string(char *copydest, const char *appsrc, int copynum);
char *concatenate_string(char *dest, const char *appsrc, int copynum);
char *locate_char(const char *searchstr, char findchars);
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
void output_error(char *output_str);
int write_char(char wc);
int write_fd(char wc, int fd);
int print_fd(char *output_str, int fd);
int str_to_int_with_error_handling(char *sc);
void eliminate_comments(char *buf);
char *parse_number(long int convnum, int convbase, int flags);

#endif

