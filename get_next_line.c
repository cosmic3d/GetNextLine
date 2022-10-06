/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:48:46 by jenavarr          #+#    #+#             */
/*   Updated: 2022/10/06 14:42:16 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	read_buffer(t_shit *things, int fd)
{
	things->bytes = read(fd, things->buffer, BUFFER_SIZE);
	if (things->bytes < 0)
		return(-1);
	things->buffer[things->bytes] = '\0';
	return (0);
}

int	whatdoido(t_shit *things, int i , int j, int what)
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
	char	*copy;
	int		ii;

	if (what == 0)
	{
		if (things->buffer[i + j] == '\n')
		{
			if (things->buffer[i + j + 1] == '\0')
				return (0);
			return (1);
		}
		return (2);
	}
	ii = ft_strlen(things->buffer);
	copy = malloc(sizeof(char) * (ft_strlen(things->buffer) + 1));
	if (copy == 0)
		return (0);
	while (ii >= 0)
	{
		copy[ii] = things->buffer[ii];
		ii--;
	}
	things->buffer = copy;
	return (0);
}

char	*allocate(t_shit *things, int fd)
{
	things->buffer = NULL;
	free(things->buffer);
	things->buffer = (char *)malloc((ssize_t)BUFFER_SIZE + 1);
	if (read_buffer(things, fd) == -1)
		return (NULL);
	things->index = 0;
	if (things->joinlater)
	{
		things->buffer = ft_strjoin(things->joinlater, things->buffer);
		free(things->joinlater);
		things->joinlater = NULL;
	}
	while (!ft_strrchr(things->buffer, '\n', 0) && things->bytes != 0)
	{
		whatdoido(things, 0, 0, 1);
		if (read_buffer(things, fd) == -1)
			return (NULL);
		things->buffer = ft_strjoin(things->tmp, things->buffer);
		free(things->tmp);
	}
	return("1");
}

char	*read_line(t_shit *things)
{
	int i;
	int j;
	int previndex;
	//char *line;
	i = 0;
	j = things->index;
	previndex = j;
	// printf("Index is: %i\n", j);
	// printf("Index character is: %c\n", things->buffer[j]);
	// printf("Buffer is: %s\n", things->buffer);
	while(things->buffer[i + j] != '\0' && things->buffer[i + j] != '\n')
		i++;
	if (whatdoido(things, i, j, 0) != 2)
	{
		things->index = i + j + 1;
		if (whatdoido(things, i, j, 0) == 1 && !ft_strrchr(things->buffer, '\n', things->index))
			things->joinlater = ft_substr(things->buffer, things->index, ft_strlen(things->buffer));
		if (things->joinlater)
			return (ft_substr(things->buffer, previndex, things->index));
		return (ft_substr(things->buffer, previndex, things->index - previndex));
	}
	things->index = i + j;
	if (things->joinlater == NULL)
		things->joinlater = ft_substr(things->buffer, previndex, i + j + 1);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_shit	things;
	
	things.line = NULL;
	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (things.buffer == NULL)
	{
		if (allocate(&things, fd) == NULL)
			return (NULL);
	}
	else if (things.buffer[things.index] == '\0')
		if (allocate(&things, fd) == NULL)
			return (NULL);
	while (things.line == NULL)
	{
		if (things.bytes == 0)
			return (things.buffer);
		things.line = read_line(&things);
		if (things.joinlater != NULL)
			if (things.buffer[things.index] == '\0' && !allocate(&things, fd))
				return (NULL);
	}
	return (things.line);
}
