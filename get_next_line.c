/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:48:46 by jenavarr          #+#    #+#             */
/*   Updated: 2022/10/04 14:46:05 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	read_buffer(t_shit *things, int fd)
{
	things->bytes = read(fd, things->buffer, BUFFER_SIZE);
	if (things->bytes < 0)
	{
		printf("\nBytes read: %i", things->bytes);
		printf("\nBuffer is: %s\n", things->buffer);
		write(1, "An error ocurred\n", 20);
		return(-1);
	}
	//printf("INDEX before assigning \'\\0\' is %i\n", things->index);
	//printf("BYTES before assigning \'\\0\' is %i\n", things->bytes);
	things->buffer[things->bytes] = '\0';
	return (0);
}

char	*allocate(t_shit *things, int fd)
{
	char	*tmp;

	things->buffer = NULL;
	free(things->buffer);
	things->buffer = (char *)malloc((ssize_t)BUFFER_SIZE + 1);
	if (read_buffer(things, fd) == -1)
		return (NULL);
	things->index = 0;
	printf("\nJoinlater is: %s\n", things->joinlater);
	if (things->joinlater)
	{
		things->buffer = ft_strjoin(things->joinlater, things->buffer);
		printf("Buffer after joinlater: %s", things->buffer);
		free(things->joinlater);
		things->joinlater = NULL;
		}
	while (!ft_strrchr(things->buffer, '\n', 0) && things->bytes != 0)
	{
		tmp = ft_strdup(things->buffer);
		if (read_buffer(things, fd) == -1)
			return (NULL);
		printf("Tmp is: %s\n", tmp);
		printf("Buffer is: %s\n", things->buffer);
		things->buffer = ft_strjoin(tmp, things->buffer);
		free(tmp);
	}
	printf("\nBuffer after joinlater is: %s\n", things->buffer);
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
	printf("Index character is: %c\n", things->buffer[j]);
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
			return (ft_substr(things->buffer, previndex, things->index));
		return (ft_substr(things->buffer, previndex, things->index));
	}
	things->index = i + j;
	if (things->joinlater == NULL)
		things->joinlater = ft_substr(things->buffer, previndex, i + j + 1);
	printf("Join later is now: %s\n", things->joinlater);
	//things->buffer = NULL;
	//free(things->buffer);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_shit	things;
	
	things.line = NULL;
	if (things.buffer == NULL)
	{
		if (allocate(&things, fd) == NULL)
			return (NULL);
	}
	else if (things.buffer[things.index] == '\0')
	{
		if (allocate(&things, fd) == NULL)
			return (NULL);
	}
	//things.line = read_line(&things);
	//if (things.line != NULL)
		//return (things.line);
	while (things.line == NULL)
	{
		if (things.bytes == 0)                                                     	return (things.buffer);
		things.line = read_line(&things);
		if (things.joinlater != NULL)
		{
			//printf("\nEntro aqui cojones\n");
			//printf("Buffer is: %s\n", things.buffer);
			if (things.buffer[things.index] == '\0')
			{
				if (allocate(&things, fd) == NULL)
					return (NULL);
			}
		}
	}
	return (things.line);
}
