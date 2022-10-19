/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:48:46 by jenavarr          #+#    #+#             */
/*   Updated: 2022/10/19 14:28:12 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"



char	*assert_line(char *buffer, int fd)
{
	char	*tmp;
	int		bytes;

	tmp = (char *)malloc((ssize_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	buffer[bytes] = '\0';
	while (!ft_strrchr(buffer, '\n', 0) && things->bytes != 0)
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
	int i;
	int prev;
	i = 0;
	prev = things->index;
	while(things->buffer[i + prev] != '\0' && things->buffer[i + prev] != '\n')//Buscamos salto de línea o \0
		i++;
	if (things->buffer[i + prev] == '\n')
	{
		things->index = i + prev + 1;
		printf("\nChar at index now is: %i\n", things->buffer[things->index]);
		if (things->buffer[i + prev + 1] != '\0' && !ft_strrchr(things->buffer, '\n', things->index))
			things->joinlater = ft_substr(things->buffer, things->index, ft_strlen(things->buffer));
		return (ft_substr(things->buffer, prev, things->index - prev));
	}
	things->index = i + prev;
	if (things->joinlater == NULL)
		things->joinlater = ft_substr(things->buffer, prev, i + prev + 1);
	return (NULL);
}

char	*get_rest(char *buffer)
{
	
}

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
	if (!ft_strrchr(buffer, '\n', 0))
	{
		buffer = 
	}
	return (line);
}
