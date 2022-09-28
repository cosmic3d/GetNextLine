/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:48:46 by jenavarr          #+#    #+#             */
/*   Updated: 2022/09/28 15:42:50 by jenavarr         ###   ########.fr       */
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
	//char *line;
	i = 0;
	j = things->index;
	previndex = j;
	len = ft_strlen(things->buffer);
	while(things->buffer[i + j] != '\0' && things->buffer[i + j] != '\n')
	{
		if (things->buffer[i + j + 1] == '\n')
		{
			things->index = i + j + 2;
			//printf("IM gonna return: %s", ft_substr(things->buffer, previndex, things->index));
			return(ft_substr(things->buffer, previndex, things->index));
		}
		if (things->buffer[i + j + 1] == '\0')
		{
			things->joinlater = ft_substr(things->buffer, previndex, i + j + 1);
			things->index = ft_strlen(things->joinlater);
			//printf("\njoinlater is: %s", things->joinlater);
			//things->buffer = NULL;
			return (NULL);
		}
		i++;
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
		if (line)
		{
			write(1, "Entra\n", 6);
			return(line);
		}
		//else
			//free(things.buffer);
	}
	bytes = read(fd, things.buffer, BUFFER_SIZE);
	if (bytes == -1)
	{
		write(1, "Entra\n", 6);
		return(NULL);
	}
	if (things.buffer[bytes - 1] != '\0')
		things.buffer[bytes] = '\0';
	if (things.joinlater)
	{
		things.buffer = ft_strjoin(things.joinlater, things.buffer);
		things.index -= ft_strlen(things.joinlater);
		free(things.joinlater);
	}
	printf("bUFFER IS: %s\n", things.buffer);
	line = read_line(&things);
	if (!line)
	{
		if (things.buffer)
			free(things.buffer);
		return (NULL);
	}
	return(line);
}