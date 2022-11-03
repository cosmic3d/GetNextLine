/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:49:16 by jenavarr          #+#    #+#             */
/*   Updated: 2022/10/23 19:37:24 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

//GET_NEXT_LINE
char	*get_next_line(int fd);
//MAIN FUNCTIONS
char	*freeshit(char **buffer);
char	*assert_line(char *buffer, int fd);
char	*erase_line(char *buffer);
char	*read_line(char	*buffer);
//UTILS FUNCTIONS
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(const char *str);
void	*ft_calloc(size_t size);
char	*ft_strrchr(const char *s, int c, int index);
#endif