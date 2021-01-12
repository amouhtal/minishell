#include "includes/minishell.h"

int count_tab(char **tab)
{
	int i;
	i = 0;

	while(tab[i])
		i++;
	return i;
}

char **ft_join_cmd(char **tab, char *arg)
{
	int i;
	char **ret;

	i = -1;
	if (!(ret = malloc(sizeof(ret) * (count_tab(tab) + 1))))
		return 0;

	while (tab[++i])
		ret[i] =ret[i] = ft_strjoin(tab[i], arg);
	ret[i] = NULL;
	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	return (ret);
}

char *if_arg_in_env(char **tab_env)
{
	int i;
	char *path;
	struct stat	stats;

	i = 0;
	while (tab_env[i])
	{
		path = tab_env[i];
		if ((stat(path, &stats)) == 0)
			if (stats.st_mode & X_OK)
				return (path);
		i++;
	}
	return (NULL);
}

char **exp_(t_env *ls)
{
    char **tab;
	int cpt;
    int i;
	while(ls->prev)
		ls = ls->prev;

		cpt = 0;
	while (ls)
		{
			ls = ls->next;
			cpt++;
		}
    tab= (char **)malloc((cpt + 1) * sizeof(char *));
    i = -1;
    while (ls)
    {
        tab[++i] = ft_strdup(ls->value);
        ls = ls->next;
    }
    tab[++i] = NULL;
    return (tab);
}

char **include_cmd(char **tab, char *cmd)
{
	int i;
	char **ret;

	i = 0;
	while (tab[i])
		i++;
	ret = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	ret[0] = ft_strdup(cmd); 
	while(tab[i])
	{
		ret[i + 1] = ft_strdup(tab[i]);
		i++;
	}
	ret[i + 1] = NULL;
	return (ret);
}

int ft_execve2(t_env *env, t_node **token,char *cmd)
{
	int i;
	char **args;
	char *path;
	char **tab;
	char **envp;
	int st;
	pid_t pid2;

	args = get_args(token);
	args = include_cmd(args, cmd);
	pid2 = fork();
	if (pid2 == 0)
	{
		i = 0;
		path = get_env_var(env, "PATH", 1);
		tab = ft_split(path, ':');
		tab = ft_join_cmd(tab, ft_strjoin("/", cmd));
		envp = exp_(env);
		if ((path = if_arg_in_env(tab)))
		{
			if (execve(path, args, envp) == -1)
				printf("Could not execve");
		}else if ((path = if_arg_in_env(&cmd )))
		{
			if (execve(path, args, envp) == -1)
				printf("Could not execve");
		}
		exit(0);
	}
	else
	{
		waitpid(pid2,&st, 0);
		return (1);
	}
	return (1);
}

int ft_execve(t_env *env, t_node **token,char *cmd)
{
	int i;
	char **args;
	char *path;
	char **tab;
	char **envp;
	// int st;
	pid_t pid2;

	args = get_args(token);
	args = include_cmd(args, cmd);
	pid2 = fork();
	if (pid2 == 0)
	{
		i = 0;
		path = get_env_var(env, "PATH", 1);
		tab = ft_split(path, ':');
		tab = ft_join_cmd(tab, ft_strjoin("/", cmd));
		envp = exp_(env);
		if ((path = if_arg_in_env(tab)))
		{
			if (execve(path, args, envp) == -1)
				printf("Could not execve");
		}
		else if ((path = if_arg_in_env(&cmd )))
		{
			if (execve(path, args, envp) == -1)
				printf("Could not execve");
		}
		exit(1);
	}
	else
	{
		wait(NULL);
		return (1);
	}
	return (1);
}