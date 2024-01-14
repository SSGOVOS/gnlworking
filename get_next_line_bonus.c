/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubine <amoubine@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:31:42 by amoubine          #+#    #+#             */
/*   Updated: 2024/01/14 16:42:34 by amoubine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strchr(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*readandjoin(int fd, char *buffer, char *str)
{
	ssize_t	i;

	while (1)
	{
		i = read(fd, str, BUFFER_SIZE);
		if (i <= 0)
			break ;
		str[i] = '\0';
		buffer = ft_strjoin(buffer, str);
		if (ft_strchr(buffer, '\n') != -1)
			break ;
	}
	free(str);
	str = NULL;
	return (buffer);
}

int	fun_tat7sb(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	return (i);
}

char	*ft_free(char *s)
{
	free(s);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*str;
	char		*nextline;
	char		*save;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = malloc((size_t)BUFFER_SIZE + 1);
	if (!str)
		return (NULL);
	buffer[fd] = readandjoin(fd, buffer[fd], str);
	if (!buffer[fd] || buffer[fd][0] == '\0')
		return (ft_free(buffer[fd]));
	i = fun_tat7sb(buffer[fd]);
	nextline = malloc(i + 1);
	if (!nextline)
		return (ft_free(buffer[fd]));
	ft_memmove(nextline, buffer[fd], i);
	nextline[i] = '\0';
	save = ft_strdup(&buffer[fd][i]);
	free(buffer[fd]);
	buffer[fd] = save;
	return (nextline);
}
// int	main(void)
// {
// 	int		i;
// 	char	*s;
// 	int		p;

// 	i = open("text.txt", O_RDONLY);
// 	s = get_next_line(i);
// 	// printf("%s" , s);
// 	// free(s);
// 	p = 0;
// 	while (p < 5)
// 	{
// 		printf("%s", s);
// 		free(s);
// 		p++;
// 		s = get_next_line(i);
// 	}
// }
