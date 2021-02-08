#include "includes/minishell.h"

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

int if_pipe_prev(t_token *token)
{
	// puts(token->str);
	while (token->prev && (token->type == ARG || token->type == CMD))
		token = token->prev;
	if (token->prev && token->type == CMD)
		token = token->prev;
	while (token && (token->type != CMD || token->type != SEP))
	{
		if (token && token->type == PIPE)
			return  PIPE;
		token = token->prev;
	}
/*	if (token->type == SEP && token->next)
		token = token->prev;
	
	while (token->prev && (token->type == ARG))
		token = token->prev;
	if (token->prev && (token->type == CMD))
		{
			token = token->prev;
			if (token->prev && token->type == PIPE)
			{
				return (1);
			}
		}*/
	return (0);
}

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
}


void get_cmd2(t_minishell *minishell)
{
	if (minishell->token && minishell->token->type == CMD)
	{
		minishell->cmd = NULL;
		minishell->cmd = ft_strdup(minishell->token->str);
		if (minishell->token->next)
			minishell->token = minishell->token->next;
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
	// int pid;
	int df = 0;
	//int stat;
	//char buff[10];
	t_token *tmp;

	minishell->nbrofpipe2 = count_pipe2(minishell->token);
	if (if_great_next(minishell->token))
	{
		close(df);
		tmp = minishell->token;
		while (tmp && tmp->type != GREAT)
			tmp = tmp->next;
		while (tmp && tmp->type == GREAT)
		{
			tmp = tmp->next;
			df = open(tmp->str , O_CREAT | O_WRONLY | O_TRUNC, 0664);
			while (tmp && tmp->type == ARG)
				tmp = tmp->next;
		}
		dup2(df, STDOUT);
	}
	if (if_append(minishell->token))
	{
			close(df);
			tmp = minishell->token;
			while (tmp && tmp->type != DOUBLE_GREAT)
				tmp = tmp->next;
			while (tmp && tmp->type == DOUBLE_GREAT)
			{
				tmp = tmp->next;
				df = open(tmp->str , O_CREAT | O_WRONLY | O_APPEND, 0664);
				while (tmp && tmp->type == ARG)
					tmp = tmp->next;
			}
			dup2(df, STDOUT);
			
	}
	if (if_input(minishell->token))
	{
			close(df);
			tmp = minishell->token;
			while (tmp && tmp->type != LESS)
				tmp = tmp->next;
			while (tmp && tmp->type == LESS)
			{
				tmp = tmp->next;
			if (tmp && (tmp->type == GREAT))
				{
					dup2(minishell->stdo, STDOUT);
					tmp = tmp->next;
				}
				//ft_putstr_fd(tmp->str, 2);
				df = open(tmp->str, O_RDONLY, S_IRWXU);
				if(df == -1)
					ft_putstr_fd("Error", 2);
				while (tmp && tmp->type == ARG)
					tmp = tmp->next;
			}
			dup2(df, STDIN);

	}
	if (minishell->token && (if_pipe_next(minishell->token) == PIPE ))
	{
    	int pipefds[minishell->nbrofpipe2 * 2];
		pid_t pid;
		int i = 0;
		int status;
		int therepipe = 1;
		int cpt = 0;
		for (i = 0; i < minishell->nbrofpipe2; i++)
		{
			if(pipe(pipefds + i * 2) < 0 )
			{
				exit(0);
			}
		}
		int j = 0;
		// exit(0);
		while(therepipe)
		{
			therepipe = if_pipe_next(minishell->token) == 0 ? 0 : 1;
		/*	if (therepipe == 2)
				therepipe = 0;
			else
			{
				therepipe = if_pipe_next(minishell->token);
				if (therepipe == 0)
					therepipe = 2;
			}*/
			pid = fork();
			if(pid == 0 )
			{
				if(if_pipe_next(minishell->token) == PIPE)
				{
					if(dup2(pipefds[(j + 1)], 1) < 0)
					{
						exit(0);
					}
				}
				if(j != 0)
				{
					if( dup2(pipefds[j - 2], 0) < 0 )
					{
							exit(0);
					}
				}
				i = 0;
				for (i = 0; i < 2 * minishell->nbrofpipe2; i++)
				{
					close(pipefds[i]);
					//i++;
				}
				if (!ft_bultins(minishell->cmd, &minishell, env))
				{
					ft_execve(env, &minishell, minishell->cmd);
				if(minishell->cmd != NULL)
					{
						free(minishell->cmd);
						minishell->cmd = NULL;
					}
				}
			}
			else if( pid < 0)
			{
				exit(0);
			}
			j += 2;
			//puts(minishell->cmd);
			// if(minishell->token->next)
			// 	{
			// 		minishell->token = minishell->token->next;
			// 		get_cmd(minishell);
			// 	}
			// 	puts(minishell->cmd);
			minishell->pid[cpt++] = pid;
			while (minishell->token && (minishell->token->type == CMD || minishell->token->type == ARG))
			{
				minishell->token = minishell->token->next;
			}
			if (minishell->token->type == PIPE)
				minishell->token = minishell->token->next;
			
			get_cmd2(minishell);
			//puts(minishell->token->str);
		}
		i = 0;
			for (i = 0; i < 2 * minishell->nbrofpipe2; i++)
			{

				close(pipefds[i]);
				//i++;
			}
			i = 0;
			for (i = 0; i < minishell->nbrofpipe2 + 1; i++)
			{
				waitpid(minishell->pid[i], &status, 0);
			//	i++;
			}
	}
	//exit(0);
	return 1;
	//}
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
		minishell->pipe = redir_pipe(minishell, env, &cpt);
		cpt++;
		//break ;
		if ((minishell->cmd && if_pipe_next(minishell->token) != PIPE &&  if_pipe_prev(minishell->token) != PIPE))
		{
			// if (minishell->token && if_pipe_prev(minishell->token) == PIPE)
			// {
			// 	close(fd[1]);
			// 	dup2(fdd, STDIN);
			// 	close(fdd);
			// }
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
		while (0 < minishell->nbrofpipe + 1)
		{
		// 	puts("*****************************");
			waitpid(minishell->pid[minishell->nbrofpipe--], &minishell->status, 0); // here
			if (WIFEXITED(minishell->status))
				minishell->exit_status = WEXITSTATUS(minishell->status);
		}
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


