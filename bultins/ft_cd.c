# include "../includes/minishell.h"


int	ft_cd( t_env *env, t_node **token)
{
	char **oldpath;
	char cwd[100];
	char *path;
	char **arg;

	arg =  get_args(token);
	//printf("%s\n",arg[0]);
	oldpath = (char**)malloc(sizeof(char *) * 3);
	oldpath[0] = ft_strdup("export");
	getcwd(cwd, sizeof(cwd));
	oldpath[1] = ft_strjoin("OLDPWD=",cwd);
	oldpath[2] = NULL;
	//printf("here\n");
	//ft_exp(env, token);
	//printf("here2\n");
	if (arg[0])
		path = arg[0];
	else
		path = get_env_var(env, "HOME", 1);
	// printf("||||||||||||%s\n",arg[0]);

	int fd;
	//char buff[128];
	fd = open("cd" , O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
//	int n;

	// while (n = read(fd, buff, 128))
	// {
		write(fd,path,ft_strlen(path));
	//}
	if (chdir(path) != 0)
		printf("chdir() to /usr failed\n"); 
	return (1);
}
