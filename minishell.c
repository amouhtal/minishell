#include "includes/minishell.h"

t_sig	sign;

void clear(t_token *first)
{
	if(first->str)
		free(first->str);
}

int count_pipe(t_token *token)
{
	int ret;
	t_token *tmp;

	tmp = token;
	ret = 0;
	while( token->prev)
		token = token->prev;
	while(token)
	{
		//printf("%d\n",token->type);
		if (token->type == PIPE)
			ret++;
		token = token->next;
	}
	token = tmp;
	return ret;
}

int count_pipe2(t_token *token)
{
	int ret;
	t_token *tmp;

	tmp = token;
	ret = 0;
	while( token->prev)
		token = token->prev;
	while(token && token->type < 4)
	{
		//printf("%d\n",token->type);
		if (token->type == PIPE)
			ret++;
		token = token->next;
	}
	token = tmp;
	return ret;
}

char **ft_cmd()
{
	char **tab;
	tab    = (char **)malloc(sizeof(char *) * 3);
	tab[0] = ft_strdup("exit");
	tab[1] = ft_strdup("..");
	tab[2] = NULL;
	return tab;
}

/*
int if_pipe_prev(t_token *token)
{
	// puts(token->str);
	while (token->prev && (token->type == ARG || token->type == CMD))
		token = token->prev;
		if (token && token->type == PIPE)
			return  PIPE;
	if (token->prev && token->type == CMD)
		token = token->prev;
	while (token && (token->type != CMD && token->type != SEP))
	{
		token = token->prev;
	}

	return (0);
}*/

int if_pipe_next(t_token *token)
{
	while(token && (token->type != CMD || token->type != SEP))
	{
		if (token && token->type == PIPE)
			return  PIPE;
		token = token->next;
	}
	return (0);
}

int if_buitins(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	return (0);
}

int ft_bultins(char *cmd, t_minishell **minishell, t_env *env)
{
	int status;
	int ret;
	ret = 1;
	// if(if_pipe_prev((*minishell)->token->prev))
	// {
	// 	ft_putstr_fd("Yeap", 2);
	// }
	if (!ft_strcmp(cmd, "echo"))
		ft_echo(minishell);
	else if (!ft_strcmp(cmd, "cd"))
		ft_cd(env, minishell);
	else if (!ft_strcmp(cmd, "pwd"))
		ft_pwd(minishell);
	else if (!ft_strcmp(cmd, "exit"))
		status = ft_exit(cmd, minishell);
	else if (!ft_strcmp(cmd, "env"))
		ft_env(env);
	else if (!ft_strcmp(cmd, "export"))
		ft_exp(&env, minishell);
	else if (!ft_strcmp(cmd, "unset"))
		ft_unset(env, minishell);
	
	if (if_buitins(cmd))
		return (1);
	else
		return (0);	
}

int if_great_next(t_token *token)
{
	while(token && (token->type != CMD || token->type != SEP))
	{
		if (token && token->type == GREAT)
			{
				return GREAT;
			}
		token = token->next;
	}
	return (0);
}

int if_append(t_token *token)
{
	// while(token && (token->type == ARG || token->type == DOUBLE_GREAT))
	while(token && (token->type != CMD || token->type == SEP))
	{
		if (token && token->type == DOUBLE_GREAT)
			return DOUBLE_GREAT;
		token = token->next;
	}
	return (0);
}

int if_input(t_token *token)
{
	while(token && (token->type == ARG || token->type == LESS))
	{
		if (token && token->type == LESS)
			return LESS;
		token = token->next;
	}
	return (0);
}

void ft_piping(t_minishell *minishell, t_env *env)
{
			dup2(minishell->fdd, STDIN);
			if (if_pipe_next(minishell->token) == PIPE)
				{
					dup2(minishell->fd[1], STDOUT);
					close(minishell->fd[1]);
				}
				close(minishell->fd[0]);
			// if (!ft_bultins(minishell->cmd, &minishell, env))
			// {
			// 	ft_execve(env, &minishell, minishell->cmd);
			// 	if(minishell->cmd != NULL)
			// 	{
			// 		free(minishell->cmd);
			// 		minishell->cmd = NULL;
			// 	}
			// }
}
void get_cmd(t_minishell *minishell)
{
	if (minishell->token && minishell->token->type == CMD)
	{
		minishell->cmd = NULL;
		minishell->cmd = ft_strdup(minishell->token->str);
		if (minishell->token->next)
			minishell->token = minishell->token->next;
		
	}
	else
	{
		if (minishell->cmd)
			{
				free(minishell->cmd);
				minishell->cmd = NULL;
			}
	}
}


void get_cmd2(t_minishell *minishell)
{
	if (minishell->token && minishell->token->type == CMD)
	{
		minishell->cmd = NULL;
		minishell->cmd = ft_strdup(minishell->token->str);
		if (minishell->token->next)
			minishell->token = minishell->token->next;
	}else
	{
		if (minishell->cmd)
			{
				free(minishell->cmd);
				minishell->cmd = NULL;
			}
	}
	
}

/*int if_pipe_next(t_token *token)
{
	while(token && (token->type != CMD || token->type != SEP))
	{
		if (token && token->type == PIPE)
			return  PIPE;
		token = token->next;
	}
	return (0);
}
*/
int redir_pipe(t_minishell *minishell, t_env *env, int *cpt)
{
	int df = 0;
	t_token *tmp;

	minishell->nbrofpipe2 = count_pipe2(minishell->token);
	if (if_great_next(minishell->token))
		ft_great(minishell);
	if (if_append(minishell->token))
		ft_append(minishell);
	if (if_input(minishell->token))
		ft_input(minishell);
	if (minishell->token && (if_pipe_next(minishell->token) == PIPE))
	{
		ft_pipe(minishell, env);
		return (1);
	}
	return (0);
}

void next_run(t_minishell **minishell)
{
	while ((*minishell)->token && ((*minishell)->token->type == PIPE || (*minishell)->token->type == GREAT 
		|| (*minishell)->token->type == LESS || (*minishell)->token->type == DOUBLE_GREAT|| (*minishell)->token->type == ARG 
		|| (*minishell)->token->type == SEP))
	{
			if ((*minishell)->token->type == SEP)
			{
				dup2((*minishell)->stdo, STDOUT);
				dup2((*minishell)->stdi, STDIN);
			}
			(*minishell)->token = (*minishell)->token->next;
	}
}

int ft_executor(t_minishell *minishell, t_env *env)
{

	int cpt = 0;
		minishell->fdd = 0;
	while (minishell->token->prev)
		minishell->token = minishell->token->prev;
	while (minishell->token)
	{

		get_cmd(minishell);
		minishell->pipe = 0;
		minishell->pipe = redir_pipe(minishell, env, &cpt);
		cpt++;
		if ((minishell->cmd && if_pipe_next(minishell->token) != PIPE) && minishell->pipe == 0)
		{
			if (!ft_bultins(minishell->cmd, &minishell, env))
				ft_execve_no_pipe(env, &minishell, minishell->cmd);
			if(minishell->cmd != NULL)
			{
				free(minishell->cmd);
				minishell->cmd = NULL;
			}
		}
		next_run(&minishell);
    }
	// while (0 < minishell->nbrofpipe + 1)
	// {
	// 	waitpid(minishell->pid_list[minishell->nbrofpipe--], &minishell->status, 0); // here
	// 	if (WIFEXITED(minishell->status))
	// 		minishell->exit_status = WEXITSTATUS(minishell->status);
	// }
	return (1);
}

void increment_shlvl(t_env *env)
{
	char *var;
	char *shlvl;

	while (env->prev)
		env = env->prev;
	while (env)
	{
		var = ft_substr((char *)env->value, 0, indexof(env->value, '=') + 1);
		if (!ft_strcmp(var, "SHLVL="))
		{
			shlvl = ft_substr(env->value, indexof(env->value, '=') + 1, ft_strlen(env->value));
			shlvl = ft_itoa(ft_atoi(shlvl) + 1);
			env->value = ft_strjoin(var, shlvl);
			break ;
		}
		env = env->next;
	}
}


