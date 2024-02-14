/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:08:56 by mhromylo          #+#    #+#             */
/*   Updated: 2023/12/28 11:50:23 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static char	*get_read(int fd, char *a, char *b)
{
	ssize_t	readed;
	char	*temp;

	readed = 1;
	while (readed > 0)
	{
		readed = read(fd, b, BUFFER_SIZE);
		if (readed == -1)
		{
			free(a);
			return (0);
		}
		else if (readed == 0)
			break ;
		b[readed] = '\0';
		if (!a)
			a = ft_strdup("");
		temp = a;
		a = ft_strjoin(temp, b);
		free(temp);
		temp = NULL;
		if (ft_strchr(b, '\n'))
			break ;
	}
	return (a);
}

char	*get_line_save(char *a)
{
	char	*str;
	ssize_t	i;

	i = 0;
	while (a[i] != '\n' && a[i] != '\0')
		i++;
	if (a[i] == '\0')
		return (0);
	str = ft_substr(a, i + 1, ft_strlen(a) - i);
	if (*str == 0)
	{
		free(str);
		str = NULL;
	}
	a[i + 1] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*a;
	char		*b;
	char		*line;

	b = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(a);
		free(b);
		a = NULL;
		b = NULL;
		return (NULL);
	}
	if (!b)
		return (NULL);
	line = get_read(fd, a, b);
	free(b);
	b = NULL;
	if (!line)
		return (NULL);
	a = get_line_save(line);
	return (line);
}
