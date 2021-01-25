#include "includes/minishell.h"

int	ft_env(t_env *env)
{
	int check;

	while (env->prev)
		env = env->prev;
	while (env)
	{
		check = indexof(env->value, '=');
		if ((int)ft_strlen(env->value) != check)
			{
				ft_putstr_fd(env->value, 1);
				ft_putstr_fd("\n", 1);
			}
			env = env->next;
	}
	return 1;
}
