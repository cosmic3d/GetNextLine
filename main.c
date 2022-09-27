/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 12:29:57 by jenavarr          #+#    #+#             */
/*   Updated: 2022/09/27 12:26:41 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int main()
{
	int fd;
	// char str[BUFFER_SIZE];
	// // char *line;


	fd = open("texto", O_RDONLY);
	if (!fd)
	{
		printf("The file could not be opened\nFinishing program\n");
		exit(1);
	}
	// printf("Read 1 is: %i\n",(int)read(fd, str, BUFFER_SIZE));
	// printf("Str is: %s\n", str);
	// printf("Read 2 is: %i\n",(int)read(fd, str, BUFFER_SIZE));
	// printf("Str is: %s\n", str);
	// // if (!read(fd, str, BUFFER_SIZE))
	// // {
	// // 	printf("The file could not be read\nFinishing program\n");
	// // 	exit(1);
	// // }
	// printf("The content is: \n\"%s\"\n", str);
	// return (0);

	int i;

	i = 0;
	while (i++ <= 2)
		printf("Line %i is: \"%s\"\n",i, get_next_line(fd));
	return (0);
	//char str[15] = "Holaquetal";

	//printf("\n%s\n", ft_substr(str, 0, 4));
}