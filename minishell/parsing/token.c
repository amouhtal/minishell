#include"../includes/minishell.h"

t_token *new_token()
{
    t_token *tmp;
    tmp = malloc(sizeof(t_token));
    tmp->type = 0;
    tmp->str = NULL;
    tmp->next = NULL;
    tmp->prev = NULL;
    return(tmp);
}
t_token *add_arg_cmd(t_token *first,char *str)
{
	t_token *new;
	int i;
	int j;

	j = 0;
	i = 0;
	new = new_token();
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