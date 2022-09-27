/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:48:46 by jenavarr          #+#    #+#             */
/*   Updated: 2022/09/27 14:34:54 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// int find_n(t_shit *things)
// {
	
// }

char	*read_line(t_shit *things)
{
	int i;
	int j;
	int len;
	int previndex;

	i = 0;
	j = things->index;
	previndex = j;
	len = ft_strlen(things->buffer);
	while(things->buffer[i + j] != '\n' && things->buffer[i + j] != '\0')
	{
		//if ()
		if (things->buffer[i + j + 1] == '\0')
			return (ft_substr(things->buffer, previndex, i + j + 1));
		i++;
	}
	if (things->buffer[i + j + 1] == '\n')
	{
		things->index = i + j + 2;
		return(ft_substr(things->buffer, previndex, things->index));
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_shit	things;
	ssize_t			bytes;
	char			*line;
	
	if (things.buffer == NULL)
	{
		things.index = 0;
		things.buffer = (char *)malloc((ssize_t)BUFFER_SIZE + 1);
	}
	else if(things.buffer != NULL)
	{
		line = read_line(&things);
		if (!line)
		{
			if (things.buffer)
				free(things.buffer);
			return (NULL);
		}
		return(line);
	}
	bytes = read(fd, things.buffer, BUFFER_SIZE);
	if (bytes == -1)
		return(NULL);
	if (things.buffer[bytes - 1] != '\0')
		things.buffer[bytes] = '\0';
	
	line = read_line(&things);
	if (!line)
	{
		if (things.buffer)
			free(things.buffer);
		return (NULL);
	}
	return(line);
}