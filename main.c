/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 12:29:57 by jenavarr          #+#    #+#             */
/*   Updated: 2022/10/20 11:54:42 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int main()
{
	int fd;
	char *str;
	// // char *line;


	fd = open("texto", O_RDONLY);
	if (!fd)
	{
		printf("The file could not be opened\nFinishing program\n");
		exit(1);
	}
	int i;

	i = 0;
	while (i++ <= 8)
	{
		str = get_next_line(fd);
		printf("LINE %i IS: %s",i, str);
		free(str);
		str = NULL;
	}
	return (0);
}
