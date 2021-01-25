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
# define STDERR 2

typedef struct token
{
	int             type;
	char            *str;
	struct token    *next;
	struct token    *prev;
}               t_token;

typedef struct s_sniffing
{
	int cntrl_c;
} t_sniffing;

typedef struct env
{
	char        *value;
	struct env  *next;
	struct env  *prev;
} t_env;

typedef struct minishell
{
	t_env   *env;
	t_token *token;
	pid_t	*pid;
	int 	nbrofpipe;
	int		current_pipe;
	int     ret;
	int		status;
	int		exit_status;
	int stdi;
	int stdo;
}           t_minishell;

void            check_fir(t_minishell *mini,char *line);
void            check_sec(t_minishell  *mini);
t_token         *add_arg_cmd(t_token *first,char *str);
t_token         *new_token();
t_env           *get_env(char **env,char **argv,int argc);
char            *fix_line(char *line);
int			    skip_quots(char *str, char c, int i);
void            ft_putstr_fd(char *s, int fd);
size_t          ft_strlen(const char *str);
char            *ft_chr(const char *s, int c);
char            *str_get(char *rest, int i, char **line);
int             get_next_line(int fd, char **line);
int             ft_bultins(char *cmd, t_minishell **minishell, t_env *env);
void            ft_bzero(void *s, size_t n);
void            *ft_calloc(size_t count, size_t size);
char            *ft_strjoin(char const *s1, char const *s2);
char            *ft_substr(char const *s, unsigned int start, size_t len);
char            *ft_strdup(const char *s1);
int             ft_strcmp(const char *s1, const char *s2);
int				ft_echo(t_minishell **minishell);
int	            ft_cd( t_env *env, t_minishell **minishell);
int 			ft_pwd(t_minishell **minishell);
int				valid_arg(t_env *env, char *arg);
int             ft_exit();
char            *ft_strtrim(char const *s1, char const *set);
char            **ft_split(char const *s, char c);
char            **ft_split_1(char *s, char c, char c1);
int             ft_env(t_env *env);
void            ft_cntr_c(int signum);
void            ft_exp(t_env **env, t_minishell **minishell);
void            ft_unset(t_env *env, t_minishell **minishell);
t_env           *add_env(t_env *list, void *value);
int             ft_isalpha(int c);
void            ft_cntr_d(int signum);
int             ft_search_variable(t_env *env, char *arg);
int             ft_unset_variable(t_env *env, char *arg);
int             indexof(char *str, char c);
char            *get_env_var(t_env *env, char *variable, int value);
int             ft_execve(t_env *env, t_minishell **minishell,char *cmd);
t_env           *get_env(char **env, char **argv, int argc);
char	        **get_args(t_minishell **minishell);
int             ft_atoi(const char *str);
char            *ft_itoa(int n);
void			increment_shlvl(t_env *env);
int count_pipe(t_token *token);
int ft_executor(t_minishell *minishell, t_env *env);
#endif
