#include"../includes/minishell.h"
int count_dollar(char *str)
{
	int i;
	int count;

	count = 0;
	i=0;
	while (str[i])
	{
		if(str[i] == '$')
			count++;
		i++;
	}
	return(count);
}
char	*get_env_variable(t_env *env, char *arg_var)
{
    char *ret;
    char *var;
	int index;

    while (env->prev)
        env = env->prev;
    while (env)
    {
		index = indexof(env->value, '=');
        var = ft_substr((char *)env->value, 0,index);
        if (!ft_strcmp(var, arg_var))
        {
			ret = ft_substr(env->value,(index+1),ft_strlen(env->value));
			
			return (ret);
        }
		env = env->next;
    }
    return (NULL);
}
char	*correct_arg_2(char *str,char *ret,char *dollar)
{
	int		lent_arg;
	char	*strr;
	int		i;
	int		j;
	int		k;
	int 	test;

	test =0;
	i = 0;
	j = 0;
	k = 0;
	lent_arg = ft_strlen(str) - ft_strlen(dollar) + ft_strlen(ret) ;
	strr = (char *)malloc(sizeof(char *) *(lent_arg +1));
	// while (str[i] != '$' && str[i] != '\0')
	// {
		
	// }

	while (str[i])
	{
		if(str[i] == '$'&& test == 0)
		{
			test = 1;
			i++;
			while (( str[i] == '_' || ft_isalpha(str[i])) && str[i] != '\0')
				i++;
			while (ret[k])
			{
				strr[j] = ret[k];
				k++;
				j++;
			}
			
		}
		strr[j] = str[i];
		i++;
		j++;
	}
	strr[j] = '\0';
	return(strr);
}
char    *get_dollar(char *str, t_env *env)
{
    int i;
    int j;
	char *dollar;
	char *ret;
	int check;
	int k;

	k= 0;
	check =0;
	if(env)
		dollar = NULL;
    j=0;
    i = 0;
    while (str[i])
    {
        if(str[i] == '$')
        {
            j = i+1;
            while ((str[j] == '_' || ft_isalpha(str[j])) && str[j] != '\0')
                j++;
			// if(j == 1 && str[j] != '\0')
			// 	j++;
			dollar =ft_substr(str,i,j);
			//printf("%d||%d||%s\n",i,j,dollar);
			ret=get_env_variable(env,&dollar[1]);
			if(ret)
			{
				if(check == 0)
					check =1;
				ret = correct_arg_2(str,ret,dollar);
				str = ft_strdup(ret);
				// printf("|%s|\n",ret);

			}
		}
		i++;	
    }
	if (check ==1)
		return(ret);
	else
		return(ft_substr(str,0,indexof(str,'$')));
}

int check_quotes_arg(char *str)
{
	int i;
	char c;


	i=0;
	while (str[i])
	{
		if(str[i] == '"' || str[i] == '\'')
		{
			c = str[i];
			i++;
			while (str[i])
			{
				if(str[i] == c || str[i] == c)
					return(str[i]);
				i++;
			}
		}	
		i++;
	}
	return(str[i]);
}

char *correct_arg(char *str,char c)
{
	char *cor_str;
	int i;
	int j;

	j =0;
	i = 0;
	cor_str = (char *)malloc(sizeof(char) * (ft_strlen(str)-1));
	while (str[i])
	{
		if(str[i]== c )
			i++;
		cor_str[j] = str[i];
		i++;
		j++;
	}
	cor_str[j]='\0';
	return(cor_str);
}

t_token *final_arg(t_token *token,t_env *env)
{
	t_token *tmp;
	char c;
    t_env *env1;

    env1=env;
	c = 'a';
	tmp = token;
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp)
	{
		if(tmp->type == ARG)
		{
			c = check_quotes_arg(tmp->str);
			if(c == '"' | c == '\'')
			{
				tmp->str = correct_arg(tmp->str,c);
			}
			if(c != '\'')
				tmp->str = get_dollar(tmp->str,env);
		}
		tmp =tmp->next;
	}
	return(token);
}
t_token *next(t_token *token)
{
	if(token->next != NULL)
		token = token->next;
	return(token);
}
void fix_token(t_token *token,int is_cmd)
{
	if(is_cmd == 0)
	{
		token = next(token);
		if(token->type == ARG)
			token->type = CMD;
		
	}	

}
void		check_sec(t_minishell *mini)
{
	t_token *tmp;
	int		is_cmd;
	int 	is_great;

	is_great = 0;
	is_cmd = 0;
	tmp = mini->token;
	while (tmp->prev)
		tmp = tmp->prev;

	while (tmp)
	{
		if(tmp->type == CMD)
			is_cmd = 1;
		else if(tmp->type == PIPE || tmp->type == SEP)
		{
			is_cmd = 0;
		}
		else if(tmp->type == GREAT)
		{
			tmp = next(tmp);
			fix_token(tmp,is_cmd);
		}
		tmp = tmp->next;
	}
	final_arg(mini->token,mini->env);
	
    //return(token);
}