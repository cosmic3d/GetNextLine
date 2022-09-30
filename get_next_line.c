/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:48:46 by jenavarr          #+#    #+#             */
/*   Updated: 2022/09/30 23:25:43 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	read_buffer(t_shit *things, int fd)
{
	int bytes;

	bytes = read(fd, things->buffer, BUFFER_SIZE);
	if (bytes <= 0)
	{
		printf("\nBytes read: %i", bytes);
		printf("\nBuffer is: %s\n", things->buffer);
		write(1, "An error ocurred or theres nothing else to read\n", 49);
		return(-1);
	}
	things->buffer[bytes] = '\0';
	return (0);
}

char	*allocate(t_shit *things, int fd)
{
	things->buffer = (char *)malloc((ssize_t)BUFFER_SIZE + 1);
	if (read_buffer(things, fd) == -1)
		return (NULL);
	things->index = 0;
	if (things->joinlater)
		things->buffer = ft_strjoin(things->joinlater, things->buffer);
	printf("\nBuffer is uwu: %s\n", things->buffer);
	return("1");
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
	printf("Index is: %i\n", j);
	printf("Buffer is: %s\n", things->buffer);
	while(things->buffer[i + j] != '\0' && things->buffer[i + j] != '\n')
		i++;
	what = whatdoido(things, i, j);
	if (what < 2)
	{
		things->index = i + j + 1;
		if (what == 1 && !ft_strrchr(things->buffer, '\n', things->index))
			things->joinlater = ft_substr(things->buffer, things->index, ft_strlen(things->buffer));
		printf("Join later now is: %s\n", things->joinlater);
		if (things->joinlater)
			return (ft_substr(things->buffer, previndex, things->index - ft_strlen(things->joinlater)));
		return (ft_substr(things->buffer, previndex, things->index));
	}
	things->index = i + j;
	if (things->joinlater == NULL)
		things->joinlater = ft_substr(things->buffer, previndex, i + j + 1);
	printf("Join later is: %s\n", things->joinlater);
	things->buffer = NULL;
	//free(things->buffer);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_shit	things;
	
	if (things.buffer == NULL)
	{
		if (allocate(&things, fd) == NULL)
			return (NULL);
	}
	things.line = read_line(&things);
	if (things.line != NULL)
		return (things.line);
	while (things.line == NULL)
	{
		//write(1, "Entrooo", 7);
		if (things.joinlater == NULL)
			things.line = read_line(&things);
		//write(1, "Entrooo", 7);
		if (things.joinlater != NULL)
		{
			//printf("\nEntro aqui cojones\n");
			printf("Buffer is: %s\n", things.buffer);
			if (things.buffer == NULL)
			{
				free(things.buffer);
				//things.buffer = NULL;
				if (allocate(&things, fd) == NULL)
					return (NULL);
			}
			else
				things.line = read_line(&things);
		}
	}
	return (things.line);
}