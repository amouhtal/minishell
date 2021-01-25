# include "../includes/minishell.h"


int	ft_cd( t_env *env, t_minishell **minishell)
{
	char *oldpath;
	char cwd[100];
	char *path;
	char **arg;
	int fd;

	arg =  get_args(minishell);
	getcwd(cwd, sizeof(cwd));
	oldpath = ft_strjoin("OLDPWD=",cwd);
	if (arg[0])
		{
			if (!ft_strcmp(arg[0], "-"))
				{
					printf("<== \n");
					path = get_env_var(env, "OLDPWD", 1);
					if (path[0] == '\0')
						ft_putstr_fd("OLDPWD not set\n", STDERR);
				}
			else
				path = arg[0];
		}
	else
		path = get_env_var(env, "HOME", 1);
	
	if (chdir(path) != 0)
	{
	
		ft_putstr_fd("changing directory failed\n", STDERR);
		(*minishell)->exit_status = 1;
	}else
	if (valid_arg(env, oldpath))
		env = add_env(env, oldpath);

	
	(*minishell)->exit_status = 0;
	return (1);
}
