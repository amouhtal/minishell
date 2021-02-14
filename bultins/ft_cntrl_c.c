#include "../includes/minishell.h"

void ft_cntr_c(int sig)
{
	int		status;
	int wpid;
	while ((wpid = wait(&status)) > 0); 
	sign.exit_status = 0;
	if (WTERMSIG(status) == SIGINT)
	{
		ft_putstr_fd("\b\b  \b\b", STDERR);
		return ;
	}
	if (sig == SIGINT)
		{
			ft_putstr_fd("\b\b  ", 2);
			ft_putstr_fd("\n\033[1;34m$minishell$~> 👾\033[0m", 2);
		}
	return ;
	signal(sig, ft_cntr_c);
}

void ft_cntr_d(int signum)
{
	int		status;
	char	*nbr;
	int wpid;

	nbr = ft_itoa(signum);
	while ((wpid = wait(&status)) > 0); 
	sign.exit_status = 0;
	printf("%d\n",sign.pid);
	if (sign.pid == 0)
	{
		ft_putstr_fd("\b\b", 2);
		ft_putstr_fd("QUIT : ", STDERR);
		ft_putstr_fd(nbr, STDERR);
		ft_putstr_fd("\n", STDERR);
		return ;
	}else
		ft_putstr_fd("\b\b  \b\b", STDERR);
	signal(signum, ft_cntr_d);
}
