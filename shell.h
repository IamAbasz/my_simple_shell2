#ifndef _SHELL_H_
#define _SHELL_H_

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

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * structs liststr - this is singly linked list
 * @numb: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int numb;
	char *str;
	structs liststr *next;
} list_t;

/**
 *structs passinfo - this mainly contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for functioning in the pointer names  structs
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@paths: a string path for the current commands
 *@argc: the argument count
 *@line_counts: the error counts
 *@err_numb: the error code for exit()s
 *@linecount_flags: if on count this line of input
 *@filname: this is the program filename
 *@envs: linked list local copy of environ
 *@environs: custom modified copy of environ from LL env
 *@history: this is the history node
 *@alias: the alias node
 *@env_changed: this is  use on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining actually 
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcounts: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *paths;
	int argc;
	unsigned int line_counts;
	int err_numb;
	int linecount_flags;
	char *filname;
	list_t *envs;
	list_t *history;
	list_t *alias;
	char **environs;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcounts;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtinn- contains a builtinn string and related function
 *@type: the builtinn command flag
 *@func: the function
 */
typedef struct builtinn
{
	char *type;
	int (*func)(info_t *);
} builtinn_table;


/* toeme_my_shloop.c */
int hsh(info_t *, char **);
int find_builtinn(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* toeme_my_parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toeme_my_errors.c */
void _erputs(char *);
int _erputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toeme_my_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* toeme_my_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toeme_my_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toeme_my_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toeme_my_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toeme_my_memory.c */
int bfree(void **);

/* toeme_my_atoi.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* toeme_my_errors1.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* toeme_my_builtinn.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* toeme_my_builtinn1.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/*toeme_my_getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* toeme_my_getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* toeme_my_environ.c */
char *_getenv(info_t *, const char *);
int _myenvs(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* toeme_my_getenv.c */
char **get_environs(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* toeme_my_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* toeme_my_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* toeme_my_lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* toeme_my_vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
