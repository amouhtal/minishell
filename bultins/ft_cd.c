# include "../includes/minishell.h"

int ft_count_args(char **args)
{
	int i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	ft_cd( t_env *env, t_minishell **minishell)
{
	char *oldpath;
	char *pwd;
	char *cpwd;
	char cwd[PATH_MAX + 1];
	char *path;
	char **arg;
	int  i = 0;
	struct stat	stt;
	
	path = malloc(PATH_MAX + 1);
	cpwd = malloc(PATH_MAX + 1);

	while (++i < PATH_MAX)
		{
			path[i] = 0;
			cpwd[i] = 0;
		}
	arg =  get_args(minishell);
	getcwd(cwd, sizeof(cwd));
	oldpath = ft_strjoin("OLDPWD=",cwd);
	sign.exit_status = 0;

	if (arg[0])
	{
		if (!ft_strcmp(arg[0], "-"))
		{
			printf("<== \n");
			path = get_env_var(env, "OLDPWD", 1);
			if (path[0] == '\0')
				ft_putstr_fd("OLDPWD not set\n", STDERR);
		}
		else if (ft_count_args(arg) > 1)
			{
				ft_putstr_fd("bash: cd: too many arguments\n", STDERR);
				sign.exit_status = 1;
			}
		else
			path = arg[0];
	}
	else
		path = get_env_var(env, "HOME", 1);
	
/*	if (lstat(path, &stt) == -1)
		ft_putstr_fd("access denied",2);
	if (!S_ISDIR(stt.st_mode))
			ft_putstr_fd("\\\\\\\\msg", 2);*/
	if (chdir(path) != 0 && ft_count_args(arg) < 2)
	{
		ft_putstr_fd("changing directory failed\n", STDERR);
		sign.exit_status = 1;
	}
	else
	{
		
	pwd = ft_strjoin("PWD=",getcwd(cpwd, 100));
	if (valid_arg(env, oldpath) /*|| valid_arg(env, pwd)*/)
		{
			//env = add_env(env, pwd);
			//env = add_env(env, oldpath);
		}
	}
	return (1);
}
