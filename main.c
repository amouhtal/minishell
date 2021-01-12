#include "includes/minishell.h"

t_node *new_node()
{
    t_node *tmp;
    tmp = malloc(sizeof(t_node));
    tmp->type = 0;
    tmp->str = NULL;
    tmp->next = NULL;
    tmp->prev = NULL;
    return(tmp);
}

t_node *link_node(t_node *first,t_node *next)
{
    t_node *tmp;

    tmp = first;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = next;
    return (first);
}

t_node *add_arg_cmd(t_node *first,char *str)
{
	t_node *new;

	new = new_node();
	while (first->prev)
		first = first->prev;
	while (first->next)
		first = first->next;
	if(str[0] == '|')
		new->type = PIPE;
	else if(str[0] == '<' && str[1] == '\0')
		new->type = LESS;
	else if(str[0] == '>' && str[1] == '\0')
		new->type = GREAT;
	else if(str[0] == '>' && str[1] == '>')
		new->type = DOUBLE_GREAT;
	else if(str[0] == ';')
		new->type = SEP;
	else
	{
		if(first->type == PIPE || first->type == SEP )
			new->type=CMD;
		else
			new->type = ARG;
	}
	new->str = ft_strdup(str);
	
	new->prev= first;
	new->next =NULL;
	first->next = new;

	return(first);
}
char *fix_line(char *line)
{
	char *fixed_line;
	int i;
	int count;
	int j;

	j=0;
	count =0;
	i = 0;
	while (line[i])
	{

		if(line[i] == '<' ||line[i] == '>'  || line[i] == '|' || line[i] == ';')
		{
			if((line[i+1] == '<' && line[i] == '<' )|| (line[i+1] == '>' && line[i] == '>' ) )
				i++;
			if(line[i-1] != ' '  && i > 0)
				count++;
			if(line[i+1] != ' ' && line[i+1] != '\0')
				count++;
		}
		i++;
	}
	fixed_line = (char *)malloc(sizeof(char) * (ft_strlen(line) + count +1 ));
	i = 0;
	while (line[i])
	{

		if(line[i] == '<' ||line[i] == '>'  || line[i] == '|' || line[i] == ';')
		{
			if(line[i-1] != ' ' && line[i-1] != line[i])
			{
				fixed_line[j] = ' ';
				j++;
			}
			fixed_line[j] = line[i];
			j++;
			if(line[i+1] != ' ' && line[i+1] != line[i])
			{
				fixed_line[j] = ' ';
				j++;
			}
			i++;
		}
		else
		{
			fixed_line[j] = line[i];
			i++;
			j++;

		}
			
	}
	fixed_line[j]='\0';
	
	return(fixed_line);
}
t_node *check(t_node *first,char *line)
{	
	int i;
    int j;
    char **tab;
    j=0;
    i= 0;
    while (line[i])
    {
        if((line[i] == ';' && line[i + 1] == ';') || (line[i] == '|' && line[i + 1] == '|' )
        ||(line[i] == ';' && line[i + 1] == '|') || (line[i] == '|' && line[i + 1] == ';') )
        {
            ft_putstr_fd("error double char:", 2);
            return(NULL);
        }
        i++;
    }
    i=1;
    line = fix_line(line);
    tab = ft_split(line,' ');
    if(tab[0][0] == '|')
        first->type = PIPE;
    else if(tab[0][0] == '<' && tab[0][1] == '\0')
        first->type = LESS;
    else if(tab[0][0] == '>' && tab[0][1] == '\0')
        first->type = GREAT;
    else if(tab[0][0] == '>' && tab[0][1] == '>')
        first->type = DOUBLE_GREAT;
    else if(tab[0][0] == ';')
        first->type = SEP;
    else
    {
            first->type=CMD;
    }
    //first->type = CMD;
    first->str = ft_strdup(tab[0]);
    while (tab[i])
    {
        first=add_arg_cmd(first,tab[i]);
        i++;
	}
		
    return (first);
}

void clear(t_node *first)
{
	if(first->str)
		free(first->str);
}

char **ft_cmd()
{
	char **tab;
	tab    = (char **)malloc(sizeof(char *) * 3);
	tab[0] = ft_strdup("exit");
	tab[1] = ft_strdup("..");
	tab[2] = NULL;
	// tab[1][1]= ft_strdup("hello 2");
	// tab[2][2] = ft_strdup("hello 3");
	return tab;
}

int if_pipe_prev(t_node *token)
{
	if (token)
		token = token->prev;
	while(token && (token->type == ARG || token->type == CMD || token->type == PIPE))
	{
		if (token && token->type == PIPE)
			return  PIPE;
		token = token->prev;
	}
	return (0);
}
int if_pipe_next(t_node *token)
{
	while(token && (token->type == ARG || token->type == CMD || token->type == PIPE))
	{
		if (token && token->type == PIPE)
			return  PIPE;
		token = token->next;
	}
	return (0);
}

int if_buitins(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	return (0);
}

int ft_bultins(char *cmd, t_node *token, t_env *env)
{
	int status;
	int ret;

	ret = 0;
	if (!ft_strcmp(cmd, "echo"))
		{
			ret = 1;
			ft_echo(&token);
		}
	else if (!ft_strcmp(cmd, "cd"))
		{
			ret = 1;
			ft_cd(env, &token);
		}
	else if (!ft_strcmp(cmd, "pwd"))
		{
			ret = 1;
			ft_pwd();
		}
	else if (!ft_strcmp(cmd, "exit"))
		{
			ret = 1;
			status = ft_exit();
		}
	else if (!ft_strcmp(cmd, "env"))
			{
				ret = 1;
				ft_env(env);
			}
	else if (!ft_strcmp(cmd, "export"))
			{
				ret = 1;
				ft_exp(&env, &token);
			}
	else if (!ft_strcmp(cmd, "unset"))
			{
				ret = 1;
				ft_unset(env, &token);
			}
	return ret;
}

int if_great_next(t_node *token)
{
	while(token && (token->type == ARG || token->type == GREAT))
	{
		if (token && token->type == GREAT)
			{
				return GREAT;
			}
		token = token->next;
	}
	return (0);
}

int if_append(t_node *token)
{
	while(token && (token->type == ARG || token->type == DOUBLE_GREAT))
	{
		if (token && token->type == DOUBLE_GREAT)
			{
				return DOUBLE_GREAT;
			}
		token = token->next;
	}
	return (0);
}
int ft_executor(t_node *first, t_env *env)
{
	//int status;
	t_node *token;
	t_node *tmp;
	int stdi;	
	int stdo;
	int df;
	stdi = 0;
	stdo = 1;
	//t_node *tmp;
	char *cmd;
	//int sta;
	int fd[2];
	int fdd = 0;
	int pid;
	//int df;
	int j = 0;
	token = first;
	//status = 1;
	//prev = 0;
	while (token->prev)
		{
			token = token->prev;
		}
	while (token)
	{
		if (token && token->type == CMD)
		{
			cmd = ft_strdup(token->str);
			// if(token->next)
			token = token->next;
		}
		if (token && if_pipe_next(token) == PIPE)
		{
			pipe(fd);
			pid = fork();
			if (pid == 0)
			{
				if (if_pipe_prev(token) == PIPE)
				{
					puts(token->str);
					dup2(fdd, stdi);
				}
				if (if_pipe_next(token) == PIPE)
				{
					dup2(fd[1], stdo);
				}
				close(fd[0]);
				if (!ft_bultins(cmd, token, env))
					ft_execve(env, &token, cmd);
				exit(1);
			}
			else if (token && pid > 0)
			{
				wait(NULL);
				close(fd[1]);
				fdd = fd[0];
			}
		}
		else if (if_great_next(token))
		{
			tmp = token;
			while (tmp && tmp->type != GREAT)
				tmp = tmp->next;
			// tmp = tmp->next;
			//printf("====> %s\n", tmp->str);
			while (tmp && tmp->type == GREAT)
			{
				if(tmp)
					tmp = tmp->next;
				puts("Im here2");
				if (tmp && tmp->type == ARG)
					tmp = tmp->next;
				puts("Im here");
				df = open(tmp->str , O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
			}
			puts("(°_!_°)");
			dup2(df, 1);
		}
		else if (if_append(token))
		{
			tmp = token;
			//printf("%s\n",tmp->str);
			tmp = tmp->next;
			df = open(tmp->str , O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
			dup2(df, 1);
		}
		else if (token || cmd)
		{
			if (if_pipe_prev(token) == PIPE)
			{
				close(fd[1]);
				dup2(fdd, stdi);
				close(fdd);
			}
			if (!ft_bultins(cmd, token, env))
				ft_execve(env, &token, cmd);
		}
		if(cmd)
			free(cmd);
		while (token && (token->type == ARG || token->type == PIPE || token->type == GREAT
		|| token->type == DOUBLE_GREAT || token->type == SEP))	
			token = token->next;
    }
	/*
      // printf("Exit status was %d\n", es);
		// waitpid(pid, &st, 0);

		/////////cd////////
			int fdcd;
			char buff[128];
			fdcd = open("cd" , O_RDONLY);
			int n;
			n = read(fdcd, buff, 128);
			buff[n] = '\0';
			chdir(buff);
			close(fdcd);
		/////////////////////
		/////// exit ///////////
		//int fdexit;
		char buff2[3];
		int fdcd2 = open("exit" , O_RDONLY);
			//printf("%d\n",fdcd2);
		int n2 = read(fdcd2, buff2, 3);
		buff2[n2] = '\0';
		//printf("|%d|\n",fdcd2);
		if (!ft_strcmp(cmd, "exit"))
			{
				//n2 = open("exit" , O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
				exit(0);
			}==
		close(fdcd2);
		///////////////////
		close(fd[1]);
		fdd = fd[0];*/
		
	//}
	return (1);
}

void increment_shlvl(t_env *env)
{
	char *var;
	char *shlvl;

	while (env->prev)
		env = env->prev;
	while (env)
	{
		
		var = ft_substr((char *)env->value, 0, indexof(env->value, '=') + 1);
		if (!ft_strcmp(var, "SHLVL="))
		{
			shlvl = ft_substr(env->value, indexof(env->value, '=') + 1, ft_strlen(env->value));
			shlvl = ft_itoa(ft_atoi(shlvl) + 1);
			env->value = ft_strjoin(var, shlvl);
			//printf("%s\n",env->value);
			break ;
		}
		env = env->next;
	}
}

void great_than()
{
	
}

int		main(int ac, char *argv[], char **env )
{
	t_env *list;
	t_node *first;
	int status;
	char *line;
	int stdi;
	int stdo;

	stdi = dup(0);
	stdo = dup(1);
	list = get_env(env,argv,ac);
	increment_shlvl(list);
	status = 1;
	signal(SIGINT, ft_cntr_c);
	signal(SIGQUIT, ft_cntr_d);
	while(status)
	{
		line = NULL;
		// int fdout;
		// int fdin;
		// int fdpipe[2];
		// pipe(fdpipe);
		first = new_node();
		ft_putstr_fd("\033[1;34m$minishell$~> 👾\033[0m", 1);
		// printf("%d\n",(int)signal(SIGINT, ft_cntr_c));
		get_next_line(0, &line);
		if (line[0])
		{
			//puts("* * * * * ** * ** * * * * * * ** * * * ** * *");
				if (!(first = check(first,line)))
					break;
	
			ft_executor(first, list);
			dup2(stdo, 1);
			dup2(stdi, 0);
			puts("\t\t(<=== execution quit without error ==>)\n\n");
			// free(first);
			// free(line);
			status++;
		}
		// printf_arg_cmd(first);
		// ft_putstr_fd(first->arg[0], 1);
		// int copy_desc = dup(0);
		
		//printf("%s\n",line);
	}
}