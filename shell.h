#ifndef SHELL_H
#define SHELL_H

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


#define TOK_DELIM " \t\r\n\a"
#define TOK_BUFSIZE 128
#define BUFSIZE 1024

extern char **environ;

/**
  * struct alin - data structure used to store state of the shell
  * @av: An array of strings representing the command-line arguments.
  * @input: A string representing the user input.
  * @args: An array of strings representing the parsed arguments of the command
  * @status: An integer representing the exit status of the last
  * executed command.
  * @counter: track the number of commands executed.
  * @_environ: An array of strings representing the environment variables.
  * @pid: A string representing the process ID of the shell.
  */

typedef struct alin
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} shell_struct;


/**
  * struct separators_l - store information about separators.
  * @sep: A character representing the separator.
  * @nxt:  A pointer to the next node in the linked list.
  */

typedef struct separators_l
{
	char sep;
	struct separators_l *nxt;
} arg_seperators;

/**
  * struct cmd_line_l - store command lines or individual commands.
  * @cmd_line: A string representing the command line.
  * @nxt: A pointer to the next node in the linked list.
  */

typedef struct cmd_line_l
{
	char *cmd_line;
	struct cmd_line_l *nxt;
} cmd_line_sep;

/**
  * struct var_list - store information about variables.
  * @var_len: The length of the variable name.
  * @value: The value of the variable.
  * @value_len: The length of the value of the variable.
  * @nxt: A pointer to the next node in the linked list.
  */

typedef struct var_list
{
	int var_len;
	char *value;
	int value_len;
	struct var_list *nxt;
} var_name;

/**
  * struct builtin_s - store information about built-in commands.
  * @name: A string representing the name of the built-in command.
  * @func_ptr: function pointer to the implementation of the built-in command.
  */

typedef struct builtin_s
{
	char *name;
	int (*func_ptr)(shell_struct *arg);
} builtin_t;

int access(const char *path, int mode);
int execve(const char *path, char *const argv[], char *const envp[]);

void cd_dot(shell_struct *arg);
void cd_home(shell_struct *arg);
void cd_to(shell_struct *arg);
void cd_previous(shell_struct *arg);
int cd_shell(shell_struct *arg);

void mem_copy(void *destination, const void *source, unsigned int size);
void *_realloc(void *old_ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdptr(char **old_ptr, unsigned int old_size,
		unsigned int new_size);

int cmp_env_name(const char *envn, const char *name);
char *_getenv(const char *name, char **_environ);
int prints_env(shell_struct *arg);

char *copies_info(const char *name, const char *value);
void set_env(char *name, char *value, shell_struct *arg);
int _setenv(shell_struct *arg);
int _unsetenv(shell_struct *arg);

int get_error(shell_struct *arg, int error_value);
char *path_126_error(shell_struct *arg);
char *env_var_error(shell_struct *arg);

char *build_cd_error(shell_struct *arg, char *msg, char *str_count, char *err);
char *get_cd_error(shell_struct *arg);
char *not_found_error(shell_struct *arg);
char *exit_shell_error(shell_struct *arg);
char *cmd_nt_found(shell_struct *arg);

int check_first_char(char *input, int *ind);
int check_dup_char(char *input, int ind);
int check_syntax_err(char *input, int ind, char last);
void _perror(shell_struct *arg, char *input, int ind, int bool);
int has_syntax_error(shell_struct *arg, char *input);

int is_current_dir(char *path, int *i);
char *_locate(char *cmd, char **_environ);
int is_executable(shell_struct *arg);
int cmd_check_error(char *dir, shell_struct *arg);
int exec_cmd(shell_struct *arg);

int exec_line(shell_struct *arg);

int exit_shell(shell_struct *arg);

ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void _checkline(char **lineptr, size_t *n, char *buff, size_t i);
char *_readline(int *endfile);

int getintlen(int num);
char *_itoa(int num);
int _atoi(char *str);

int main(int ac, char **av);
void sigint_handler(int sig);
void free_shell_struct(shell_struct *arg);
void set_shell_struct(shell_struct *arg, char **av);

char *replace_ip(var_name **head, char *input, char *new_input, int new_len);
void check_envn(var_name **h, char *in, shell_struct *arg);
int var_check(var_name **h, char *in, char *st, shell_struct *arg);
char *replace_var(char *input, shell_struct *arg);

var_name *add_var_node(var_name **head, int lvar, char *val, int lval);
void free_var_list(var_name **head);

char *char_swap(char *input, int bool);
void add_node(arg_seperators **sep_head, cmd_line_sep **cmdline_head,
		char *input);
void go_next(arg_seperators **separator_list,
		cmd_line_sep **command_line_list, shell_struct *arg);
int split_commands(shell_struct *arg, char *input);

cmd_line_sep *add_cmdln_end(cmd_line_sep **head, char *cmd_line);
void free_cmdln_list(cmd_line_sep **head);
arg_seperators *add_separators_end(arg_seperators **head, char separator);
void free_separators_l(arg_seperators **head);

void shell_prompt(shell_struct *arg);
char *remove_comment(char *input);

int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
int _strcmp(char *str1, char *str2);
char *_strdup(const char *s);

char *strchr(const char *s, int c);
size_t _strspn(const char *s, const char *accept);
int _isNumeric(const char *s);
void rev_string(char *s);

int (*_builtin(char *cmd))(shell_struct *);
int execute_arg(shell_struct *arg);

char *_strtok(char *str, const char *delim);
char **split_line(char *input);
int cmp_chars(char str[], const char *delim);

#endif
