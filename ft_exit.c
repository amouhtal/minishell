#include "includes/minishell.h"

int	ft_strisnum(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int ft_exit(char *cmd, t_minishell **minishell)
{
	char **arg;
	int exit_nbr;
	int i;

	i = 0;
	if(cmd)
		cmd =NULL;
	arg =  get_args(minishell);
	exit_nbr = 0;
	if (arg[1])
		ft_putstr_fd("exit: too many arguments\n", 2);
	else
	{
		if (arg[0])
		{
			if (ft_strisnum(arg[0]) == 0)
			{
				ft_putstr_fd("exit: ", 2);
				ft_putstr_fd(arg[0], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				exit_nbr = 255;
			}
			else
				exit_nbr = ft_atoi(arg[0]);
		}
		/*puts("  ////   \t  ////");
		puts(" (°>°)   \t (°>°)");
		puts("__| |__  \t__| |__");
		puts("--   --  \t--   -- ");
		puts(" ) | )   \t ) | )");
		puts("( ( )    \t( ( )");
		puts(" |||     \t |||");
		puts(" > >     \t  > >");*/
		exit(exit_nbr);
	}
	
		//printf("%s\n", arg[0]);

	//if( if_pi)
	return 0;
}