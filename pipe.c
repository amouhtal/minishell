#include "includes/minishell.h"

void    ft_close_fds(t_minishell *minishell, int *pipefds)
{
    int i;
    int status;

    i = 0;
	while (i < 2 * minishell->nbrofpipe2)
	{
		close(pipefds[i]);
        i++;
	}
	i = 0;
	if (!minishell->nbrofpipe2)
		waitpid(sign.pid, &status, 0);
	while (i < minishell->nbrofpipe2 )
	{
		waitpid(minishell->pid_list[i], &minishell->status, 0);
		if (WIFEXITED(minishell->status))
			sign.exit_status = WEXITSTATUS(minishell->status);
        i++;
	}
}

void ft_pipe(t_minishell *minishell, t_env *env)
{
    	int pipefds[minishell->nbrofpipe2 * 2];
		int i = 0;
		int status;
		int therepipe = 1;
		int cpt = 0;
		while (i < minishell->nbrofpipe2)
		{
			if(pipe(pipefds + i * 2) < 0 )
				exit(0);
			i++;
		}
		int j = 0;
		while(therepipe)
		{
			therepipe = if_pipe_next(minishell->token) == 0 ? 0 : 1;
			sign.pid = fork();
			if(sign.pid == 0 )
			{
				if(if_pipe_next(minishell->token) == PIPE)
					if(dup2(pipefds[(j + 1)], 1) < 0)
						exit(0);
				if(j != 0)
					if(dup2(pipefds[j - 2], 0) < 0)
						exit(0);
				i = 0;
				while (i < 2 * minishell->nbrofpipe2)
					close(pipefds[i++]);
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
			else if(sign.pid < 0)
				exit(0);
			j += 2;
			minishell->pid_list[cpt++] = sign.pid;
			while (minishell->token && (minishell->token->type == CMD || minishell->token->type == ARG || minishell->token->type == LESS))
				minishell->token = minishell->token->next;
			if (minishell->token->type == PIPE)
				minishell->token = minishell->token->next;
			get_cmd(minishell);
		}
		ft_close_fds(minishell, pipefds);
}
