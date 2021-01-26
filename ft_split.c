/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hamr <mel-hamr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 17:32:18 by mel-hamr          #+#    #+#             */
/*   Updated: 2021/01/26 17:32:01 by mel-hamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static	int			c_word(char *str, char c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			i = skip_quots(str, str[i],i);
				//printf("|%c|",ptr[nn+1]);
		}
		if (str[i] == c && str[i + 1] != c)
			count++;
		if (str[i] != c && str[i + 1] == '\0')
			count++;
	}
	return (count);
}

static	void		ft_free(char **tab, char *str)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(str);
}

static	char		*remplir(char *s, int *k, char c)
{
	int		i;
	int		start;
	int		end;
	char	*str;
	int startt;
	i = *k;
	while (s[i] == c)
		i++;
	start = i;
	startt = i;
	while (s[i] != c && s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			i = skip_quots(s, s[i],i);
				//printf("|%c|",ptr[nn+1]);
		}
		i++;
	
	}
	end = i;
	*k = i;
	while(startt < end)
	{
		//printf("%c",s[startt]);
		startt++;
	}
		//printf("|%d|",end -start);
	str = ft_substr(s, start, (end - start ));
	//printf("%s\n",str);
	if (str == NULL)
		return (NULL);
	return (str);
}

char				**ft_split(char const *s, char c)
{
	char	*str;
	char	**tab;
	int		i;
	int		j;
	int		k;

	if (s == NULL)
		return (NULL);
	i = -1;
	str = ft_strtrim(s, &c);
	if (str == NULL)
		return (NULL);
	j = c_word(str, c);
	//printf("|%d|",j);
	tab = (char **)malloc((j + 1) * sizeof(char*));
	if (tab == NULL)
		return (NULL);
	k = 0;
	while (++i < j)
		if ((tab[i] = remplir(str, &k, c)) == NULL)
		{
			ft_free(tab, str);
			return (0);
		}
	tab[i] = 0;
	return (tab);
}
