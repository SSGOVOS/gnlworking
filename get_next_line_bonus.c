/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubine <amoubine@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 01:12:14 by amoubine          #+#    #+#             */
/*   Updated: 2023/12/31 13:29:05 by amoubine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char *ft_strchr(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (&s[i]);
		i++;
	}
	return (0);
}

char	*readandjoin(int fd, char *buffer)
{
	int readed;
	if (!buffer)
	{
		buffer = ft_calloc(1, 1);
		*buffer = 0;
	}
	char *str = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!str)
	{
		free(buffer);
		return(NULL);
	}
	readed = 1;
	*str = 0;
	while (!ft_strchr(buffer, '\n') && readed != 0)
	{
		readed = read(fd, str, BUFFER_SIZE);
		if (readed < 0)
		{
			free(buffer);
			free(str);
			return (NULL);
		}
		str[readed] = '\0';
		buffer = ft_strjoin(buffer, str);
		if (!buffer)
		{
			free(str);
			return (NULL);
		}
	}
	free(str);
	return (buffer);
}

char *read_from_buffer(char *buffer)
{
	int	i;
	char *line;
	if (!buffer[0])
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(sizeof(char) *(i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = 0;
	return (line);
}
char *update_buffer(char *buffer)
{
	char *new;
	int i;
	int j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	new = malloc(sizeof(char) *( ft_strlen(buffer) - i + 1));
	if (!new)
	{
		free(buffer);
		return (NULL);
	}
	i++;
	j = 0;
	while (buffer[i])
		new[j++] = buffer[i++];
	new[j] = 0;
	free(buffer);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*nextline;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = readandjoin(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	nextline = read_from_buffer(buffer[fd]);
	buffer[fd] = update_buffer(buffer[fd]);
	return (nextline);
}