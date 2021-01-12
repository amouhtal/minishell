#include "../includes/minishell.h"

int		nb_args(char **args)
{
	int		size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}

// int tab_rows(t_node **token)
// {
// 	int i;
// 	t_node *tmp;

// 	tmp = *token;
// 	i = 0;
// 	while (tmp && tmp->next && tmp->type == ARG)
// 	{
// 		i++;
// 		tmp = tmp->next;
// 	}
// 	if (tmp && tmp->type == ARG)
// 		i++;
// 	return (i);
// }

int				ft_echo(t_node **token)
{
	int		i;
	int		n_option;
	int cpt;
	char **args;

	
	args = get_args(token);

	i = 0;
	n_option = 0;
	cpt = 0;
	while (args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		n_option = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1] && args[i][0] != '\0')
			write(1, " ", 1);
		i++;
	}
	if (n_option == 0)
		write(1, "\n", 1);
	return (1);
}
