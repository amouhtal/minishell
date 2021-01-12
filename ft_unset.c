#include "includes/minishell.h"

int ft_unset_variable(t_env *env, char *arg_var)
{
	struct env *tmp_n;
	t_env *tmp_env;
	char *var;

	while (env->prev)
		env = env->prev;
	while (env)
	{
		tmp_n = env->next;
		tmp_env = env;
		var = ft_substr((char *)env->value, 0, indexof(env->value, '='));
		if (!ft_strcmp(var, arg_var))
		{
			env = env->prev;
			env->next = tmp_env->next;
			env = tmp_env->next;
			if (tmp_env->next)
				env->prev = tmp_env->prev;
			free(tmp_env);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

void ft_unset(t_env *env, t_node **token)
{
	int i;
	char **args;

	args = get_args(token);
	i = 0;
	while (args[i])
	{
		ft_unset_variable(env, args[i]);
		i++;
	}
}
