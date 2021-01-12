#include "../includes/minishell.h"

int ft_pwd()
{
	char *current_dir;

	current_dir = malloc(sizeof(char) * 20);
	//current_dir = current_dirft_strdup(getcwd(, 100));

	ft_putstr_fd(getcwd(current_dir, 100), 1);
	ft_putstr_fd("\n", 1);
	return (1);
}