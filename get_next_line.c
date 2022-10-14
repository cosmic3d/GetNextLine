/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:48:46 by jenavarr          #+#    #+#             */
/*   Updated: 2022/10/14 21:13:36 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*freethings(t_shit *things, int buffer, int s)
{
	if (buffer == 1)
	{
		free(things->buffer);
		things->buffer = NULL;
		//printf("\nBuffer freed: %s\n", things->buffer);
	}
	if (s == 1)
	{
		things = NULL;
		//printf("Struct null\n");
	}
	return (NULL);
}

int	read_buffer(t_shit *things, int fd)
{
	things->bytes = read(fd, things->buffer, BUFFER_SIZE);
	if (things->bytes == -1)
	{
		write(1, "An error occurred\n", 19);
		return(NULL);
	}
	printf("Bytes read are: %i\n", things->bytes);
	things->buffer[things->bytes] = '\0';
	return (1);
}

char	*assert_line(t_shit *things, int fd)
{
	char	*tmp;
	
	things->buffer = (char *)malloc((ssize_t)BUFFER_SIZE + 1);
	things->index = 0;
	if (!read_buffer(things, fd))
		return (NULL);
	buff = read_buffer(things, fd, buff);
	if (!buff)
		return (freethings(things, 1, 1));
	things->index = 0;
	if (things->joinlater)
		buff = ft_strjoin(things->joinlater, buff);
	while (!ft_strrchr(buff, '\n', 0) && things->bytes != 0)
	{
		tmp = ft_strdup(buff);
		buff = read_buffer(things, fd, buff);
		if (!buff)
			return (freethings(things, 1, 1));
		buff = ft_strjoin(tmp, buff);
	}
	return("1");
}

char	*read_line(t_shit *things)
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

char	*get_next_line(int fd)
{
	static t_shit	things;
	char			*line;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (freethings(&things, 1, 1));
	if (things.buffer == NULL)
	{
		if (!assert_line(&things, fd))
			return (NULL);
	}
	line = read_line(&things);
	if (!line)
		return (freethings(&things, 1, 1));
	if (things.joinlater)
		freethings(&things, 1, 0);
	printf("\nJoinlater is: %s\n", things.joinlater);
	return (line);
}
