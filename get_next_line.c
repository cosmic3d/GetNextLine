/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:48:46 by jenavarr          #+#    #+#             */
/*   Updated: 2022/10/13 22:57:35 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*freethings(t_shit *things, int buffer, int joinlater, int line, int s)
{
	if (buffer == 1 && things->buffer)
	{
		free(things->buffer);
		things->buffer = NULL;
		//printf("\nBuffer freed: %s\n", things->buffer);
	}
	if (joinlater == 1 && things->joinlater)
	{
		free(things->joinlater);
		things->joinlater = NULL;
		//printf("Joinlater freed\n");
	}
	if (line == 1)
	{
		//free(things->line);
		things->line = NULL;
		//printf("Line freed\n");
	}
	if (s == 1 && things)
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
		free(things->buffer);
		return(-1);
	}
	//printf("Bytes read are: %i\n", things->bytes);
	things->buffer[things->bytes] = '\0';
	return (0);
}

char	*assert_line(t_shit *things, int fd)
{
	char	*tmp;

	things->buffer = (char *)malloc((ssize_t)BUFFER_SIZE + 1);
	if (!things->buffer)
		return (NULL);
	if (read_buffer(things, fd) == -1)
		return (freethings(things, 1, 1, 0, 1));
	things->index = 0;
	if (things->joinlater)
	{
		things->buffer = ft_strjoin(things->joinlater, things->buffer);
		freethings(things, 0, 1, 0, 0);
	}
	while (!ft_strrchr(things->buffer, '\n', 0) && things->bytes != 0)
	{
		tmp = ft_strdup(things->buffer);
		if (read_buffer(things, fd) == -1)
			return (freethings(things, 1, 1, 0, 1));
		things->buffer = ft_strjoin(tmp, things->buffer);
	}
	printf("\nBuffer is: %s\n", things->buffer);
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
		if (things->buffer[i + prev + 1] == '\0' && !ft_strrchr(things->buffer, '\n', things->index))
			things->joinlater = ft_substr(things->buffer, things->index, ft_strlen(things->buffer));
		if (things->joinlater)
			return (ft_substr(things->buffer, prev, things->index - prev));
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

	things.line = NULL;
	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (freethings(&things, 1, 1, 1, 1));
	if (things.buffer == NULL)
	{
		things.buffer = ft_strdup("");
		if (!assert_line(&things, fd))
			return (NULL);
	}
	line = read_line(&things);
	if (!line)
		return (freethings(&things, 1, 1, 0, 1));
	if (things.joinlater)
		free(things.buffer);
	printf("\nJoinlater is: %s\n", things.joinlater);
	return (line);
}
