/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:48:46 by jenavarr          #+#    #+#             */
/*   Updated: 2022/09/19 14:37:05 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(t_shit *things)
{
	int i;
	int j;

	i = 0;
	j = things->index;
	while(things->buffer[i] != '\n' && things->buffer[i] != '\0')
	{

	}
}

char	*get_next_line(int fd)
{
	static t_shit things;
	ssize_t bytes;

	if (things.buffer == NULL)
	{
		things.index = 0;
		things.buffer = (char *)malloc((ssize_t)BUFFER_SIZE);
	}
	else if(things.buffer != NULL)
	{

	}
	bytes = read(fd, things.buffer, BUFFER_SIZE);
	if (bytes == -1)
		return(0);
	free(things.buffer);
}