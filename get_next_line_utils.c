/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 15:48:49 by jenavarr          #+#    #+#             */
/*   Updated: 2022/09/30 22:51:38 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new)
		return (0);
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		new[i] = s2[j];
		j++;
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	ft_strlen(const char *str)
{
	int	length;

	length = 0;
	while (str[length])
		length++;
	return (length);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	char	*new;
	size_t	i;

	size = 0;
	i = 0;
	while (s[i++])
		size++;
	i = 0;
	if (start >= size)
		new = malloc(sizeof(char) * 1);
	else if (len > size - start)
		new = malloc(sizeof(char) * (size - start + 1));
	else
		new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	while (start + i < size && i < len)
	{
		new[i] = s[i + start];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_strrchr(const char *s, int c, int index)
{
	while (s[index] != '\0')
	{
		if (s[index] == (char)c)
			return ((char *)(s + index));
		index++;
	}
	return (NULL);
}