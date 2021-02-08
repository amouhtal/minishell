#include "includes/minishell.h"

t_env *new_env(void *value)
{
	t_env *new;
    new = malloc(sizeof(t_env));
    new->next = NULL;
    new->prev = NULL;
	new->value = ft_strdup(value);
    return(new);
}

t_env *add_env(t_env *list, void *value)
{
	t_env *new;
	if (!list || !value)
		return (NULL);
	while(list->next)
		list = list->next;
	new = malloc(sizeof(t_env));
	new->next = NULL;
	new->prev = list;
	new->value = ft_strdup(value);
	list->next = new;
		// puts("here\n");
	return (list);
}

t_env *get_env(char **env,char **argv,int argc)
{   
    t_env *list;
    int i;
	if(argc < 0)
		argv[0]=NULL;
	i = 1;
	list = new_env(env[0]);
	while (env[i])
	{
		list = add_env(list, env[i]);
		i++;
	}
	return (list);
}