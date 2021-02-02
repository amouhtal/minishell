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
	t_env *tmp;
	int cpt;
    int i;

	while(ls->prev)
		ls = ls->prev;
	tmp = ls;
	cpt = 0;
	while (tmp)
	{
		tmp = tmp->next;
		cpt++;
	}
    tab = (char **)malloc((cpt + 1) * sizeof(char *));
    i = -1;
    while (ls)
    {
        tab[++i] = ft_strdup(ls->value);
        ls = ls->next;
    }
    tab[i + 1] = NULL;
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

int ft_execve(t_env *env, t_minishell **minishell,char *cmd)
{
	int i = 0;
	char **args;
	int j = -1;
	char *path;
	char **tab;
	char **envp;
	// int st;
	pid_t pid;
	// pid_t pid2;

	args = get_args(minishell);
	while(args[i])
		i++;
	args = include_cmd(args, cmd);
	i = 0;
	path = get_env_var(env, "PATH", 1);
	tab = ft_split(path, ':');
	tab = ft_join_cmd(tab, ft_strjoin("/", cmd));
	envp = exp_(env);
	pid = fork(); 
	if (pid == 0)
	{
		if ((path = if_arg_in_env(tab)))
		{
			if (execve(path, args, envp) == -1)
				ft_putstr_fd("Could not execve", 3);
			// execve(path, args, envp);
			// puts("\n\n\n\n\nhere");
		}
		else if ((path = if_arg_in_env(&cmd)))
		{
			if (execve(path, args, envp) == -1)
				ft_putstr_fd("Could not execve", 3);
			// puts("\n\n\n\n\nhere");
			// execve(path, args, envp);
		}else
		{
			if (!ft_strcmp("minishell", cmd))
				increment_shlvl(env);
			else
			{
				ft_putstr_fd(cmd, 2);
				ft_putstr_fd(": command not found\n",2);
				exit(127);
			}
		}
		exit(0);
	}
	else
	{
		// if (!(*minishell)->nbrofpipe)
		// 	waitpid(pid, &(*minishell)->status, 0);
		// else
		// {
		// 	while (++j < (*minishell)->nbrofpipe + 1)
		// 		waitpid((*minishell)->pid[j], &(*minishell)->status, 0);
		// }
			// wait(NULL);
		//	sleep(1);
		if (WIFEXITED((*minishell)->status))
		{
			(*minishell)->exit_status = WEXITSTATUS((*minishell)->status);
			return ((*minishell)->exit_status);
			// printf("Exit status of the child was %d\n",  (*minishell)->exit_status);
		}
		return (1);
	}
	return (1);
}