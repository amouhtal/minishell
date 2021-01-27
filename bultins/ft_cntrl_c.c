#include "../includes/minishell.h"

void ft_cntr_c(int signum)
{
	ft_putstr_fd("\b\b  ", 1);
	ft_putstr_fd("\n\033[1;34m$minishell$~> 👾\033[0m", 1);
	signal(signum, ft_cntr_c);
}

void ft_cntr_d(int signum)
{
	ft_putstr_fd("\b\b", 1);
	ft_putstr_fd("QUIT\n", 1);
	exit(0);
	signal(signum, ft_cntr_d);
}
