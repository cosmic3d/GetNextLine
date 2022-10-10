/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:48:46 by jenavarr          #+#    #+#             */
/*   Updated: 2022/10/10 14:34:56 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	read_buffer(t_shit *things, int fd)
{
	things->bytes = read(fd, things->buffer, BUFFER_SIZE);
	if (things->bytes < 0)
		return(-1);
	//printf("Bytes read are: %i\n", things->bytes);
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
	if (copy == NULL)
		return (-1);
	while (ii >= 0)
	{
		copy[ii] = things->buffer[ii];
		ii--;
	}
	things->tmp = copy;
	return (0);
}

char	*allocate(t_shit *things, int fd)
{
	things->buffer = NULL;
	//free(things->buffer);
	things->buffer = (char *)malloc((ssize_t)BUFFER_SIZE + 1);
	if (things->buffer == NULL)
		return(NULL);
	if (read_buffer(things, fd) == -1)
		return (NULL);
	things->index = 0;
	if (things->joinlater)
	{
		things->buffer = ft_strjoin(things->joinlater, things->buffer);
		//free(things->joinlater);
		things->joinlater = NULL;
	}
	while (!ft_strrchr(things->buffer, '\n', 0) && things->bytes != 0)
	{
		if (whatdoido(things, 0, 0, 1) == -1 || read_buffer(things, fd) == -1)
			return (NULL);
		things->buffer = ft_strjoin(things->tmp, things->buffer);
		if (things->tmp)
			free(things->tmp);
		if (!things->buffer)
			return (freethings(things, 1, 1, 1, 1));
	}
	return("1");
}

char	*read_line(t_shit *things)
{
	int i;
	int j;
	int previndex;
	i = 0;
	j = things->index;
	previndex = j;
	while(things->buffer[i + j] != '\0' && things->buffer[i + j] != '\n')//Buscamos salto de línea o \0
		i++;
	if (whatdoido(things, i, j, 0) != 2)//Si da distinto de dos, hay un salto de línea
	{
		things->index = i + j + 1;
		if (whatdoido(things, i, j, 0) == 1 && !ft_strrchr(things->buffer, '\n', things->index))
			things->joinlater = ft_substr(things->buffer, things->index, ft_strlen(things->buffer));
		if (things->joinlater)
			return (ft_substr(things->buffer, previndex, things->index - previndex));
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
	
	freethings(&things, 0, 0, 1, 0);
	//things.line = NULL;
	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (freethings(&things, 1, 1, 1, 1));
	//printf("Index is: %i\n", things.index);
	if (things.buffer == NULL)
	{
		if (allocate(&things, fd) == NULL)
			return (freethings(&things, 1, 1, 1, 1));
	}
	else if (things.buffer[things.index] == '\0')
		if (allocate(&things, fd) == NULL)
			return (freethings(&things, 1, 1, 1, 1));
	while (things.line == NULL)
	{
		if (things.bytes == 0)
		{
			if (!(things.buffer[things.index] != '\0'))
				return (freethings(&things, 1, 1, 1, 1));
			whatdoido(&things, 0, 0, 1);
			things.line = things.tmp;
			things.buffer = NULL;
			return (things.line);
		}
		things.line = read_line(&things);
		if (things.joinlater != NULL)
			if (things.buffer[things.index] == '\0' && !allocate(&things, fd))
				return (freethings(&things, 1, 1, 1, 1));
	}
	return (things.line);
}
