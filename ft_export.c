#include "includes/minishell.h"


int ft_search_variable(t_env *env, char *arg)
{
	char *tmp;
	char *var;
	char *arg_var;

	while (env->prev)
		env = env->prev;
	
	while (env)
	{
		arg_var = ft_substr(arg, 0, indexof(arg, '='));
		var = ft_substr((char *)env->value, 0, indexof(env->value, '='));
		if(!ft_strcmp(var, arg_var))
		{

			tmp = env->value;
			env->value = (void *)ft_strdup(arg);
			free(tmp);
			return (1);
		}
		env = env->next;
	}
	return (0);
}
int valid_arg(t_env *env, char *arg)
{
	int i;

	i= 0;
	//if (ft_isalpha(arg[0]) || arg[0] == '_')
	// while(arg[i] && arg[i] != '=')
	// 	i++;
	//ft_putstr_fd(&arg[i], 1);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (0);
	}
	if (ft_search_variable(env, arg))
		return (0);
	return (1);
}

char *get_env_var(t_env *env, char *variable, int value)
{
	char *env_var;
	char *ret;

	ret = NULL;
	while (env->prev)
		env = env->prev;
	while (env)
	{
		env_var = ft_substr((char *)env->value, 0, indexof(env->value, '='));
		if(!ft_strcmp(env_var, variable))
			break;
		env = env->next;
	}
	if (value == 1)
		ret = ft_substr((char *)env->value, indexof(env->value, '=') + 1, ft_strlen(env->value));
	ret = ft_substr((char *)env->value, indexof(env->value, '=') + 1, ft_strlen(env->value));
	return (ret);
}



char **sorted_table(t_env *env)
{
	int i;
	int j;
	char *tmp;
	char **ret;
	i = 0;
	while (env->prev)
		env = env->prev;
	while (env->next)
	{
			env = env->next;
			i++;
	}
	if (!(ret = (char **)malloc(sizeof(char *) * (i + 1))))
		return NULL;
	j = 0;
	while (env->prev)
		env = env->prev;
	while (env->next)
	{
		ret[j] = line_of_env(env->value);
		env = env->next;
		j++;
	}
	ret[j++] = line_of_env(env->value);
	ret[j] = NULL;
	j = 0;
	while (j < i)
	{
		if (ft_strcmp(ret[j], ret[j + 1]) > 0 && ret[j + 1] != NULL)
		{
			tmp = ret[j];
			ret[j] = ret[j + 1];
			ret[j + 1] = tmp;
			j = -1;
		}
		j++;
	}
	// i = 0;
	// while (ret[i])
	// 	{
	// 		ft_putstr_fd("declare -x ", 1);
	// 		i++;
	// 	}
	return ret;
}

void ft_exp(t_env **env, t_minishell **minishell)
{
	int i;
	char **exptab;
	char **args;

	args = get_args(minishell);
	exptab = sorted_table((*env));
	i = 0;
	if (!args[0])
		while (exptab[i])
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(exptab[i], 1);
			ft_putstr_fd("\n", 1);
			i++;
		}
	else
		while (args[i])
		{
			
			if (valid_arg((*env), args[i]))
			{
				(*env) = add_env((*env), args[i]);
			}
			i++;
		}
	// int i;

	// i = 1;
	// if (!args[1])
	// {
	// 	while (env->prev)
	// 	{
	// 		env = env->prev;
	// 		//cpt++;
	// 	}
	// 	while (env)
	// 	{
	// 		ft_putstr_fd("declare -x ", 1);
	// 		ft_putstr_fd(env->value, 1);
	// 		ft_putstr_fd("\n", 1);
	// 		env = env->next;
	// 	}
	// }
}
