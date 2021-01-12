/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhtal <amouhtal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 18:51:32 by amouhtal          #+#    #+#             */
/*   Updated: 2020/12/23 15:44:27 by amouhtal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static	int		countwords(char *ptr, char c, char c1)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (ptr[i])
	{
		if ((ptr[i] == c || ptr[i] == c1))
			count++;
		i++;
	}
	return (count + 1);
}

static	char	*affectation(char c, char c1, int *ii, char *ptr)
{
	int		k;
	char	*p;
	int		n;

	k = 0;
	n = 0;
	while ((ptr[*ii + n] != c && ptr[*ii + n] != c1) && ptr[*ii + n])
		n++;
	if (!(p = (char *)malloc(sizeof(char) * (n + 1))))
		return (NULL);
	while (n > k)
	{
		p[k] = ptr[k + *ii];
		k++;
	}
	p[k] = '\0';
	*ii = n + *ii;
	return (p);
}

static	void	free_news(char **news)
{
	int i;

	i = 0;
	while (news[i])
	{
		free(news[i]);
		i++;
	}
}

char			**ft_split_1(char  *s, char c, char c1)
{
	int		index;
	char	**news;
	int		i;
	int		j;

	j = 0;
	if (!(news = (char **)malloc(sizeof(char*) * (countwords(s, c, c1) + 1))))
		return (0);
	i = 0;
	index = -1;
	while (s[i] )
	{
		if (s[i] == c || s[i] == c1)
			i++;
		if ((news[++index] = affectation(c, c1, &i, s)) == NULL)
		{
			free_news(news);
			free(s);
			return (0);
		}
		j++;
	}
	news[index + 1] = NULL;
	return (news);
}
