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
	if (token)
		token = token->prev;
	while(token && (token->type != CMD || token->type != SEP))
	{
		if (token && token->type == PIPE)
			return  PIPE;
		token = token->prev;
	}
	return (0);
}

int if_pipe_next(t_token *token)
{
	while(token && (token->type != CMD || token->type != SEP))
	{
		if (token && token->type == PIPE)
			{
				return  PIPE;
			}
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
	//	puts(cmd);		
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
	while(token && (token->type == ARG || token->type == DOUBLE_GREAT))
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

void redir_pipe(t_minishell *minishell, t_env *env, char *cmd, int fd[2], int *fdd,int *cpt)
{
	//int pid;
	int df = 0;
	//int stat;
	//char buff[10];
	t_token *tmp;
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
				ft_putstr_fd(tmp->str, 2);
				df = open(tmp->str, O_RDONLY, S_IRWXU);
				if(df == -1)
					ft_putstr_fd("Error", 2);
				while (tmp && tmp->type == ARG)
					tmp = tmp->next;
			}
			dup2(df, STDIN);

	}
	if (minishell->token && if_pipe_next(minishell->token) == PIPE)
	{
		pipe(fd);
		minishell->pid[*cpt] = fork();
		if (minishell->pid[*cpt] == 0)
		{
			if (if_pipe_prev(minishell->token) == PIPE)
				dup2(*fdd, STDIN);
			if (if_pipe_next(minishell->token) == PIPE)
				dup2(fd[1], STDOUT);
			close(fd[0]);
			
			if (!ft_bultins(cmd, &minishell, env))
			{
				ft_execve(env, &minishell, cmd);
				if(cmd != NULL)
				{
					free(cmd);
					cmd = NULL;
				}
			}
			exit(1);
		}
		else if (minishell->pid[minishell->current_pipe++] > 0)
		{
			while(minishell->token && minishell->token->type == ARG)
				minishell->token = minishell->token->next;
					//return (minishell->exit_status);
			close(fd[1]);
			*fdd = fd[0];
		}
	}
	// ft_putstr_fd( ft_strjoin("\n333",minishell->token->str), 2);
}

void next_run(t_minishell **minishell)
{
	
	
	// while ((*minishell)->token)
	// {
	// 	if ((*minishell)->token->type == PIPE)
	// 	{
	// 		(*minishell)->token = (*minishell)->token->next;
	// 		break;
	// 	}
	// 	if ((*minishell)->token->type == ARG  || (*minishell)->token->type == GREAT || (*minishell)->token->type == LESS || (*minishell)->token->type == DOUBLE_GREAT
	// 	|| (*minishell)->token->type == SEP)
	// 	{
	// 		(*minishell)->token = (*minishell)->token->next;
	// 	}else if ((*minishell)->token->type == CMD)
	// 	{
	// 		break;
	// 	}
	// 	(*minishell)->token = (*minishell)->token->next;
	// }

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
	//inishell)->token = (*minishell)->token->next;
	}
}

int ft_executor(t_minishell *minishell, t_env *env)
{
	int fd[2];
	int fdd;
	char *cmd;
	int cpt = 0;
	cmd = NULL;
	while (minishell->token->prev)
		minishell->token = minishell->token->prev;
	while (minishell->token)
	{
		if (minishell->token && minishell->token->type == CMD)
		{
			cmd = ft_strdup(minishell->token->str);
			minishell->token = minishell->token->next;
		}
		redir_pipe(minishell, env, cmd, fd, &fdd, &cpt);
		cpt++;
		if ((cmd && if_pipe_next(minishell->token) != PIPE))
		{
			if (minishell->token && if_pipe_prev(minishell->token) == PIPE)
			{
				close(fd[1]);
				dup2(fdd, STDIN);
				close(fdd);
			}
			if (!ft_bultins(cmd, &minishell, env))
				ft_execve(env, &minishell, cmd);
			if(cmd != NULL)
			{
				free(cmd);
				cmd = NULL;
			}
		}
		next_run(&minishell);
    }
	// while(waitid(P_ALL, 0, NULL, WEXITED) != 0)
    // 	perror("waitid failed:");
	while (0 < minishell->nbrofpipe)
	{
		waitpid(minishell->pid[minishell->nbrofpipe--], &minishell->status, 0);
		if (WIFEXITED(minishell->status))
			minishell->exit_status = WEXITSTATUS(minishell->status);
	}
	
	
	//if (if_pipe_next(minishell->token) != PIPE)
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


