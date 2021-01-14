#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#define BUFFER_SIZE 50

#define LESS 4
#define GREAT 7
#define PIPE 3
#define DOUBLE_GREAT 77
#define CMD 1
#define ARG 2
#define SEP 5

# define STDIN  0
# define STDOUT 1

typedef struct node
{
    int type;
    char *str;
    struct node *next;
    struct node *prev;
} t_node;

typedef struct s_sniffing
{
    int cntrl_c;
} t_sniffing;

typedef struct env
{
    char *value;
    struct env *next;
    struct env *prev;
} t_env;

typedef struct minishell
{
    t_env *env;
    t_node *token;
} t_minishell;

void ft_putstr_fd(char *s, int fd);
size_t ft_strlen(const char *str);
char *ft_chr(const char *s, int c);
char *str_get(char *rest, int i, char **line);
int get_next_line(int fd, char **line);
int ft_bultins(char *cmd, t_node **token, t_env *env);
void ft_bzero(void *s, size_t n);
void *ft_calloc(size_t count, size_t size);
char *ft_strjoin(char const *s1, char const *s2);
char *ft_substr(char const *s, unsigned int start, size_t len);
char *ft_strdup(const char *s1);
int ft_strcmp(const char *s1, const char *s2);
int ft_echo(t_node **token);
int ft_cd(t_env *env, t_node **token);
int ft_pwd();
int ft_exit();
char *ft_strtrim(char const *s1, char const *set);
char **ft_split(char const *s, char c);
char **ft_split_1(char *s, char c, char c1);
int ft_env(t_env *env);
void ft_cntr_c(int signum);
void ft_exp(t_env **env, t_node **token);
void ft_unset(t_env *env, t_node **token);
t_env *add_env(t_env *list, void *value);
int ft_isalpha(int c);
void ft_cntr_d(int signum);
int ft_search_variable(t_env *env, char *arg);
int ft_unset_variable(t_env *env, char *arg);
int indexof(char *str, char c);
char *get_env_var(t_env *env, char *variable, int value);
int ft_execve2(t_env *env, t_node **token, char *cmd);
int ft_execve(t_env *env, t_node **token, char *cmd);
t_env *get_env(char **env, char **argv, int argc);
char **get_args(t_node **token);
int ft_atoi(const char *str);
char *ft_itoa(int n);
#endif
