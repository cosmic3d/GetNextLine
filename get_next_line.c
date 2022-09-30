/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:48:46 by jenavarr          #+#    #+#             */
/*   Updated: 2022/09/30 13:03:30 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	read_buffer(t_shit *things, int fd)
{
	ssize_t bytes;

	bytes = read(fd, things->buffer, BUFFER_SIZE);
	if (bytes <= 0)
	{
		write(1, "An error ocurred or theres nothing else to read\n", 49);
		return(-1);
	}
	things->buffer[bytes] = '\0';
}

int whatdoido(t_shit *things, int i , int j)
{
	/*
	If it finds a \n
		If there is a \0 next to the \n
			We set the index to i + j + 1 and return previndex to index
		If there is something different to a \0 next to the \n
			We set the index to i + j + 1, save everything from index to ft_strlen(buffer) and return previndex to index
	If it finds a \0 there are two possibilities:
		1 - The buffer size was greater or equal than the size of the file, so we just have to return that line and end the program
		2 - The buffer size was lower than the size of the file, so we have to keep joining strings till we find a \n
	*/
	if (things->buffer[i + j] == '\n')
	{
		if (things->buffer[i + j + 1] == '\0')
			return (0);
		return (1);
	}
	return (2);
}

char	*read_line(t_shit *things)
{
	int i;
	int j;
	int previndex;
	int	what;
	//char *line;
	i = 0;
	j = things->index;
	previndex = j;
	while(things->buffer[i + j] != '\0' && things->buffer[i + j] != '\n')
		i++;
	what = whatdoido(things, i, j);
	if (what < 2)
	{
		things->index = i + j + 1;
		if (what == 1)
			things->joinlater = ft_substr(things->buffer, things->index, ft_strlen(things->buffer));
		return (ft_substr(things->buffer, previndex, things->index));
	}
	things->index = i + j;
	things->joinlater = ft_substr(things->buffer, previndex, i + j + 1);
	things->buffer = NULL;
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
		while (line == NULL)
			line = read_line(&things);
		return(line);
	}
	if (read_buffer(&things, fd) == -1)
		return (NULL);
	// if (things.joinlater)
	// {
	// 	things.buffer = ft_strjoin(things.joinlater, things.buffer);
	// 	things.index -= ft_strlen(things.joinlater);
	// 	free(things.joinlater);
	// }
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