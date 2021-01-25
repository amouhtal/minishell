#include "includes/minishell.h"

int		main(int ac, char *argv[], char **env )
{
	t_minishell minishell;

	int status;
	char *line;
	minishell.env = get_env(env,argv,ac);
	increment_shlvl(minishell.env);
	status = 1;
	signal(SIGINT, ft_cntr_c);
	signal(SIGQUIT, ft_cntr_d);
	while(status)
	{
		line = NULL;
		minishell.token = new_token();
		ft_putstr_fd("\033[1;34m$minishell$~> 👾\033[0m", 1);
		int r = get_next_line(0, &line);
		if (r == 0)
			{
				ft_putstr_fd("exit\n", 1);
				exit(0);
			}
		if (line[0])
		{
			minishell.stdi = dup(0);
			minishell.stdo = dup(1);
			check_fir(&minishell,line);
			check_sec(&minishell);
			minishell.pid = malloc(sizeof(pid_t) * (minishell.nbrofpipe = count_pipe(minishell.token)));
			minishell.current_pipe = 0;
			ft_executor(&minishell, minishell.env);
			free(minishell.token);
			dup2(minishell.stdo, STDOUT);
			dup2(minishell.stdi, STDIN);
			// printf("$? == %d\n",  minishell.exit_status);
			status++;
		}
	}
}
