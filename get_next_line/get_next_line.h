/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateak <ateak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 14:10:54 by cpollito          #+#    #+#             */
/*   Updated: 2022/09/06 12:43:27 by ateak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# define BUFFER_SIZE 42

char	*get_next_line(int fd);
char	*ft_memmove_gnl(char *dst, char *src, size_t n);
char	*ft_strjoin(const char *s1, char const *s2);
char	*ft_strjoin_gnl(const char *s1, char const *s2, int len);
int		ft_strchr_gnl(const char *s, int c);
size_t	ft_strlen(const char *str);
#endif