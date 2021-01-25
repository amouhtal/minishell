#include"../includes/minishell.h"

int count_lent(char *line)
{
	int i;
	int count;

	count =0;
	i = 0;
	while (line[i])
	{

		if (line[i] == '\'' || line[i] == '"')
			i = skip_quots(line, line[i ], i);
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
	return(count);
}

void	fill_btw_qutes(char *line,char *fixed_line,int *i,int *j,char c)
{
	fixed_line[*j] = line[*i];
	*i = *i+1;
	*j = *j+1;
	while (line[*i] != c && line[*i])
	{
		fixed_line[*j] = line[*i];
		*i = *i+1;
		*j = *j+1;
	}
}
char *fix_line(char *line)
{
	char *fixed_line;
	int i;
	int j;

	j=0;
	fixed_line= (char *)malloc(sizeof(char) * (ft_strlen(line) + count_lent(line) +1 ));
	i=0;
	while (line[i])
	{
		if(line[i] == '"' || line[i] =='\'')
			fill_btw_qutes(line,fixed_line,&i,&j,line[i]);
		if(line[i] == '<' ||line[i] == '>'  || line[i] == '|' || line[i] == ';')
		{
			if(line[i-1] != ' ' && line[i-1] != line[i])
				fixed_line[j++] = ' ';
			fixed_line[j++] = line[i];
			if(line[i+1] != ' ' && line[i+1] != line[i])
				fixed_line[j++] = ' ';
			i++;
		}
		else
			fixed_line[j++] = line[i++];
	}
	fixed_line[j]='\0';
	return(fixed_line);
}

void	check_fir(t_minishell *mini,char *line)
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
			ft_putstr_fd("error double char : ", 2);
			break;
		}
		i++;
	}
	i=1;
	line = fix_line(line);
	tab = ft_split(line,' ');
	if(tab[0][0] == '|')
		mini->token->type = PIPE;
	else if(tab[0][0] == '<' && tab[0][1] == '\0')
		mini->token->type = LESS;
	else if(tab[0][0] == '>' && tab[0][1] == '\0')
		mini->token->type = GREAT;
	else if(tab[0][0] == '>' && tab[0][1] == '>')
		mini->token->type = DOUBLE_GREAT;
	else if(tab[0][0] == ';')
		mini->token->type = SEP;
	else
	{
			mini->token->type=CMD;
	}
	//token->type = CMD;
	mini->token->str = ft_strdup(tab[0]);
	while (tab[i])
	{
		mini->token=add_arg_cmd(mini->token,tab[i]);
		i++;
	}
	//return (0);
}