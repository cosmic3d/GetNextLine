/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:48:46 by jenavarr          #+#    #+#             */
/*   Updated: 2022/10/19 15:43:12 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"



char	*assert_line(char *buffer, int fd)
{
	char	*tmp;
	int		bytes;

	tmp = (char *)malloc((ssize_t)BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	while (!ft_strrchr(buffer, '\n', 0) && bytes != 0)
	{
		bytes = read(fd, tmp, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			free(tmp); 
			return (NULL);
		}
		tmp[bytes] = '\0';
		buffer = ft_strjoin(buffer, tmp);
	}
	free(tmp);
	return(buffer);
}

char	*read_line(char	*buffer)
{
	int		i;
	char	*line;
	
	i = 0;
	while(buffer[i] != '\0' && buffer[i] != '\n')//Buscamos salto de línea o \0
		i++;
	if (buffer[i] == '\n')
	{
		line = ft_substr(buffer, 0, i);
		if (!line)
		{
			free(buffer);
			return (NULL);
		}
		while(*buffer != '\n')
			buffer++;
		buffer++;
		return (line);
	}
	return (buffer);
}

// char	*get_rest(char *buffer)
// {
// 	char	*rest;

// 	if (*buffer != '\0' && !ft_strrchr(buffer, '\n', 0))
// 	{
// 		rest = ft_substr(buffer)
// 	}
// }

char	*get_next_line(int fd)
{
	static	char	*buffer;
	char			*line;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (buffer == NULL)
	{
		buffer = ft_strdup("");
		if (!buffer)
			return (NULL);
	}
	buffer = assert_line(buffer, fd);
	if (!buffer)
		return (NULL);
	line = read_line(buffer);
	if (!line)
		return (NULL);
	// if (!ft_strrchr(buffer, '\n', 0))
	// {
	// 	buffer = get_rest(buffer);
	// 	if (!buffer)
	// 		return (NULL);
	// }
	return (line);
}
