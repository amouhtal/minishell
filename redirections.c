#include "includes/minishell.h"

void    ft_great(t_minishell *minishell)
{
	t_token *tmp;

    close(minishell->fd_out);
	tmp = minishell->token;
	while (tmp && tmp->type != GREAT)
		tmp = tmp->next;
	while (tmp && tmp->type == GREAT)
	{
		tmp = tmp->next;
		minishell->fd_out = open(tmp->str , O_CREAT | O_WRONLY | O_TRUNC, 0664);
		while (tmp && tmp->type == ARG)
			tmp = tmp->next;
	}
	dup2(minishell->fd_out, STDOUT);

}

void    ft_append(t_minishell *minishell)
{
	t_token *tmp;
	
	close(minishell->fd_out);
	tmp = minishell->token;
	while (tmp && tmp->type != DOUBLE_GREAT)
		tmp = tmp->next;
	while (tmp && tmp->type == DOUBLE_GREAT)
	{
		tmp = tmp->next;
		minishell->fd_out = open(tmp->str , O_CREAT | O_WRONLY | O_APPEND, 0664);
		while (tmp && tmp->type == ARG)
			tmp = tmp->next;
	}
	dup2(minishell->fd_out, STDOUT);
}

void    ft_input(t_minishell *minishell)
{
	t_token *tmp;
    close(minishell->fd_in);
	tmp = minishell->token;
	while (tmp && tmp->type != LESS)
		tmp = tmp->next;
	while (tmp && tmp->type == LESS)
	{
		tmp = tmp->next;
		if (tmp && (tmp->type == GREAT))
		{
			//dup2(minishell->stdo, STDOUT);
			tmp = tmp->next;
		}
		minishell->fd_in = open(tmp->str, O_RDONLY, S_IRWXU);
		if (minishell->fd_in == -1)
			ft_putstr_fd("Error", 2);
		while (tmp && tmp->type == ARG)
			tmp = tmp->next;
	}
	dup2(minishell->fd_in, 0);
}
