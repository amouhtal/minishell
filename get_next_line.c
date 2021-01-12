/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhtal <amouhtal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:52:11 by amouhtal          #+#    #+#             */
/*   Updated: 2020/12/23 15:44:33 by amouhtal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

size_t			ft_strlen(const char *str)
{
	size_t		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char			*ft_chr(const char *s, int c)
{
	char		c2;
	char		*str;
	int			i;

	c2 = (char)c;
	str = (char *)s;
	i = 0;
	if (c2 == '\0')
		return (str + ft_strlen(str));
	while (str[i])
	{
		if (str[i] == c2)
			return (str + i);
		i++;
	}
	return (NULL);
}

char			*str_get(char *rest, int i, char **line)
{
	char		*ptr;

	while (rest[i])
	{
		if (rest[i] == '\n')
		{
			free(*line);
			*line = ft_substr(rest, 0, i);
			ptr = rest;
			rest = ft_strdup(rest + i + 1);
			free(ptr);
			return (rest);
		}
		i++;
	}
	if (rest[0] != '\0')
	{
		free(*line);
		*line = ft_substr(rest, 0, i);
		ptr = rest;
		free(ptr);
		return (NULL);
	}
	free(rest);
	return (NULL);
}

int				get_next_line(int fd, char **line)
{
	char		*buff;
	static char	*rest;
	int			j;
	char		*ptr;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > 4864 || read(fd, NULL, 0) < 0
		|| !line || !(buff = (char *)malloc((sizeof(char)) * BUFFER_SIZE + 1)))
		return (-1);
	*line = ft_strdup("\0");
	if (rest == NULL)
		if (!(rest = ft_calloc(1, 1)))
			return (-1);
	while ((!ft_chr(rest, '\n')) && (j = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[j] = '\0';
		ptr = rest;
		rest = ft_strjoin(rest, buff);
		free(ptr);
	}
	free(buff);
	if (j < 0)
		free(rest);
	if (j < 0)
		return (-1);
	return (((rest = str_get(rest, 0, line)) == NULL) ? 0 : 1);
}
