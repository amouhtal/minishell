/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhtal <amouhtal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:52:16 by amouhtal          #+#    #+#             */
/*   Updated: 2020/12/23 15:44:36 by amouhtal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char			*ft_strdup(const char *s1)
{
	int			i;
	char		*str;

	i = 0;
	while (s1[i])
		i++;
	if (!(str = (char*)malloc((i + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*ab;
	size_t		i;

	i = 0;
	if (s == 0)
		return (NULL);
	if (start > len)
		return (ft_strdup(""));
	ab = (char *)malloc((len + 1) * sizeof(char));
	if (ab == NULL)
		return (NULL);
	while (s[start + i] && i < len)
	{
		ab[i] = s[start + i];
		i++;
	}
	ab[i] = '\0';
	return (ab);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	char		*mm;
	size_t		i;
	size_t		j;
	size_t		k;

	j = 0;
	k = 0;
	if (s1 && s2)
	{
		i = ft_strlen(s1) + ft_strlen(s2);
		mm = (char*)malloc((i + 1) * sizeof(char));
		if (mm == NULL)
			return (NULL);
		i = 0;
		while (s1[i])
			mm[j++] = s1[i++];
		while (s2[k])
			mm[j++] = s2[k++];
		mm[j] = '\0';
		return (mm);
	}
	return (NULL);
}

void			*ft_calloc(size_t count, size_t size)
{
	void		*hep;

	hep = (void*)malloc(count * size);
	if (hep == NULL)
		return (NULL);
	ft_bzero(hep, count * size);
	return (hep);
}

void			ft_bzero(void *s, size_t n)
{
	size_t		cont;
	char		*s2;

	cont = 0;
	s2 = (char *)s;
	while (cont < n)
	{
		s2[cont] = 0;
		cont++;
	}
}
