/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:48:46 by jenavarr          #+#    #+#             */
/*   Updated: 2022/10/21 22:25:12 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*freeshit(char **buffer)
{
	if (buffer != NULL)
	{
		if (*buffer)
			free(*buffer);
		buffer = NULL;
	}
	return (NULL);
}

char	*erase_line(char *buffer)
{
	char	*new;
	int		i;

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	new = ft_substr(buffer, i + 1, ft_strlen(buffer) - i + 1);
	if (!new)
		return (NULL);
	freeshit(&buffer, NULL);
	return (new);

}

char	*assert_line(char *buffer, int fd)
{
	char	*tmp;
	int		bytes;

	tmp = (char *)malloc((ssize_t)BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	while (!ft_strrchr(buffer, '\n', 0) && bytes != 0)
	{
		bytes = read(fd, tmp, BUFFER_SIZE);
		if (bytes == -1)
			return (freeshit(&buffer, &tmp));
		tmp[bytes] = '\0';
		buffer = ft_strjoin(buffer, tmp);
	}
	free(tmp);
	return(buffer);
}

char	*read_line(char	*buffer)
{
	int		i;
	char	*line;
	
	i = 0;
	while(buffer[i] != '\0' && buffer[i] != '\n')//Buscamos salto de línea o \0
		i++;
	line = ft_substr(buffer, 0, i + 1);
	if (!line)
		return (NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static	char	*buffer;
	char			*line;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (buffer == NULL)
	{
		buffer = ft_strdup("");
		if (!buffer)
			return (NULL);
	}
	buffer = assert_line(buffer, fd);
	if (!buffer)
		return (NULL);
	line = read_line(buffer);
	if (!line)
		return (freeshit(&buffer, NULL));
	if (*line == '\0')
		return (freeshit(&buffer, &line));
	buffer = erase_line(buffer);
	if (!buffer)
		return (freeshit(&line, NULL));
	return (line);
}
