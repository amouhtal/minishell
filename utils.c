#include "includes/minishell.h"

int     ft_strcmp(const char *s1, const char *s2)
{
    size_t i;
    i = 0;
    if ((!s1 || !s2))
        return (1);
    while ((s1[i] || s2[i]))
    {
        if (s1[i] != s2[i])
            return ((unsigned char)s1[i] - (unsigned char)s2[i]);
        i++;
    }
    return (0);
}
int     indexof(char *str, char c)
{
    int i = 0;
    while(str[i])
    {
        if(str[i] == c)
            return i;
        i++;
    }
    return(i);
}

int			skip_quots(char *str, char c, int i)
{
	int j;

	j = i + 1;
	while (str[j])
	{
		if(str[j] == c )
		{
			return(j);
		}
		j++;
	}
	return(j);
}

void	ft_putstr_fd(char *s, int fd)
{
	int i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}


static	int		checkset(char c, char *set)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	char	*cpyset;
	int		len;

	str = ft_strdup(s1);
	if (str == NULL)
		return (NULL);
	cpyset = (char *)set;
	while (checkset(str[0], cpyset) == 1)
		str++;
	len = ft_strlen(str) - 1;
	while (len > 0)
	{
		if (checkset(str[len], cpyset) == 0)
			break ;
		str[len] = '\0';
		len--;
	}
	return (ft_strdup(str));
}

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
	{
		return (1);
	}
	return (0);
}
int		tab_rows(t_token *token)
{
	int i;
			

	i = 0;
	while (token && token->type == ARG )
	{
		if(token->type == ARG )
		i++;
		token = token->next;
	}
	// if ((*token) && (*token)->type == ARG)
	// 	i++;
	return (i);
}

char	**get_args(t_minishell **minishell)
{
	char **args;
	int i;
	int size;
	size = tab_rows((*minishell)->token);
	i = 0;
	args = (char **)malloc(sizeof(char *) * (size + 1));
	while (i < size)
	{
		args[i] = ft_strdup((*minishell)->token->str);
		(*minishell)->token = (*minishell)->token->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}
