/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:30:06 by jenavarr          #+#    #+#             */
/*   Updated: 2022/10/28 15:06:29 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	i = -1;
	j = 0;
	new = (void *)ft_calloc((size_t)(ft_strlen(s1) + ft_strlen(s2) + 1));
	if (new == NULL)
		return (freeshit(&s1));
	while (s1[++i] != '\0')
		new[i] = s1[i];
	while (s2[j] != '\0')
	{
		new[i] = s2[j];
		j++;
		i++;
	}
	freeshit(&s1);
	return (new);
}

int	ft_strlen(const char *str)
{
	int	length;

	length = 0;
	if (!str)
		return (0);
	while (str[length])
		length++;
	return (length);
}

void	*ft_calloc(size_t size)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = (char *)malloc(sizeof(char) * size);
	if (!ptr)
		return (NULL);
	while (i < size)
		ptr[i++] = 0;
	return (ptr);
}

char	*ft_strrchr(const char *s, int c, int index)
{
	if (s)
	{
		while (s[index] != '\0')
		{
			if (s[index] == (char)c)
				return ((char *)(s + index));
			index++;
		}
	}
	return (NULL);
}
