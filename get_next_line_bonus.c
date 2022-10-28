/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:48:46 by jenavarr          #+#    #+#             */
/*   Updated: 2022/10/28 14:23:21 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*freeshit(char **buffer)
{
	free(*buffer);
	*buffer = NULL;
	buffer = NULL;
	return (NULL);
}

char	*erase_line(char *buffer)
{
	char	*new;
	int		i;
	int		c;

	if (!buffer)
		return (freeshit(&buffer));
	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\0')
		return (freeshit(&buffer));
	c = 0;
	new = ft_calloc(ft_strlen(buffer) - i + 1);
	if (!new)
		return (NULL);
	i++;
	c = 0;
	while (buffer[i])
		new[c++] = buffer[i++];
	freeshit(&buffer);
	return (new);
}

char	*assert_line(char *buffer, int fd)
{
	char	*tmp;
	int		bytes;

	tmp = (char *)malloc((ssize_t)BUFFER_SIZE + 1);
	if (tmp == NULL)
		return (freeshit(&buffer));
	while (!ft_strrchr(buffer, '\n', 0) && bytes != 0)
	{
		bytes = read(fd, tmp, BUFFER_SIZE);
		if (bytes < 0)
		{
			freeshit(&buffer);
			return (freeshit(&tmp));
		}
		tmp[bytes] = '\0';
		buffer = ft_strjoin(buffer, tmp);
	}
	freeshit(&tmp);
	return (buffer);
}

char	*read_line(char	*buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
		line = (char *)malloc(sizeof(char) * (i + 1));
	else
		line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = -1;
	while (buffer[++i] != '\0' && buffer[i] != '\n')
		line[i] = buffer[i];
	if (buffer[i] == '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char		*buffer[OPEN_MAX];
	char			*line;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (buffer[fd] == NULL)
	{
		buffer[fd] = ft_strdup("");
		if (!buffer[fd])
			return (NULL);
	}
	buffer[fd] = assert_line(buffer[fd], fd);
	if (!buffer[fd])
		return (freeshit(&buffer[fd]));
	line = read_line(buffer[fd]);
	buffer[fd] = erase_line(buffer[fd]);
	return (line);
}
