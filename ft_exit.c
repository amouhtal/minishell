#include "includes/minishell.h"

int ft_exit(char *cmd, t_minishell **minishell)
{
	char **arg;
	int exit_nbr;

	if(cmd)
		cmd =NULL;
	arg =  get_args(minishell);
	exit_nbr = 0;
	if (arg[1])
		ft_putstr_fd("exit: too many arguments\n", 2);
	else
	{
		if (arg[0])
			exit_nbr = ft_atoi(arg[0]);
		puts("  ////   \t  ////");
		puts(" (°>°)   \t (°>°)");
		puts("__| |__  \t__| |__");
		puts("--   --  \t--   -- ");
		puts(" ) | )   \t ) | )");
		puts("( ( )    \t( ( )");
		puts(" |||     \t |||");
		puts(" > >     \t  > >");
		exit(exit_nbr);
	}
	
		//printf("%s\n", arg[0]);

	//if( if_pi)
	return 0;
}