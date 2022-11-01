/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:24:24 by jenavarr          #+#    #+#             */
/*   Updated: 2022/10/28 14:44:23 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
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
char	*ft_strdup(const char *s1);
#endif
