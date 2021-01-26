#include "includes/minishell.h"

// char	**exp(t_env *ls)
// {
//     char	**tab;
//     int		i;
//     tab = (char **)malloc(ft_lstsize(ls) * sizeof(char *) +1);
//     i = -1;
//     while (ls)
//     {
//         tab[++i] = ft_strdup(ls->value);
//         ls = ls->next;
//     }
//     tab[++i] = NULL;
//     return (tab);
// }
// int get_env_variable(t_env *env, char *arg_var)
// {
//     struct env *tmp_n;
//     t_env *tmp_env;
//     char *var;
//     while (env->prev)
//         env = env->prev;
//     while (env)
//     {
//         tmp_n = env->next;
//         tmp_env = env;
//         var = ft_substr((char *)env->value, 0, indexof(env->value, '='));
//         if (!ft_strcmp(var, arg_var))
//         {
//             env = env->prev;
//             env->next = tmp_env->next;
//             env = tmp_env->next;
//             if (tmp_env->next)
//                 env->prev = tmp_env->prev;
//             free(tmp_env);
//             return (1);
//         }
//         env = env->next;
//     }
//     return (0);
// }
void get_first(t_env **env)
{
	while ((*env)->prev)
	{
		(*env) = (*env)->prev;
	}
	
}
void printf_arg_cmd(t_token *first)
{
	int i;

	i= 0;
	while (first->prev)
		first = first->prev;
	while (first->next)
	{
		printf("type=%d\n",first->type);
		printf("str=%s\n",first->str);
		printf("=============================\n");
		first=first->next;
	}
	printf("type=%d\n",first->type);
	printf("str=%s\n",first->str);
	printf("=============================\n");
	i = 0;
}
void test(t_token *token)
{
		while (token->prev)
		token = token->prev;
}
int main(int argc, char **argv, char **env)
{
	t_minishell minishell;
 	char *line;
	int s;
	int status;
	// t_env *temp;
	s = 1;
	minishell.env=get_env(env,argv,argc);
	increment_shlvl(minishell.env);
	status = 1;
	signal(SIGINT, ft_cntr_c);
	signal(SIGQUIT, ft_cntr_d);
	//get_first(&list);
	// temp = mini.env;
	// while (temp->prev)
	// 	temp = temp->prev;
		
	// while (temp)
	// {
	// 	printf("%s\n",temp->value);
	// 	temp= temp->next;
	// }
	
	while(status)
	{
		line = NULL;
		minishell.token = new_token();
		ft_putstr_fd("\033[1;34m$minishell$~> 👾\033[0m", 1);
		int r = get_next_line(0, &line);
		if (r == 0)
			{
				ft_putstr_fd("exit\n", 1);
				exit(0);
			}
		if(line[0] != '\0')
		{
			minishell.stdi = dup(0);
			minishell.stdo = dup(1);
			//puts("here");
			check_fir(&minishell,line);
			check_sec(&minishell);
			//printf_arg_cmd(minishell.token);
			// printf("%s\n",mini.token->str);
			// test(mini.token);
			//  printf("%s\n",mini.token->str);
			minishell.pid = malloc(sizeof(pid_t) * (minishell.nbrofpipe = count_pipe(minishell.token)));
			minishell.current_pipe = 0;
			ft_executor(&minishell, minishell.env);
			dup2(minishell.stdo, STDOUT);
			dup2(minishell.stdi, STDIN);
			free(minishell.token);
			//free(minishell.token);
		}
	}
	return 0;
}