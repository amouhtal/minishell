#include "../includes/minishell.h"

int ft_pwd(t_minishell **minishell)
{
	int i;
	char current_dir[PATH_MAX + 1];
	i = 0;

	while (++i < PATH_MAX)
		current_dir[i] = 0;
	//current_dir = current_dirft_strdup(getcwd(, 100));
	//ft_putstr_fd("current_dir", 1);
	if (getcwd(current_dir, 100))
		ft_putstr_fd(current_dir, 1);
	else
		ft_putstr_fd(current_dir, 1);
	ft_putstr_fd("\n", 1);
	sign.exit_status = 0;
	return (1);
}