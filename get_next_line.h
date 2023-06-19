/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:18:08 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/01/08 20:03:58 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <stdbool.h>

char			*ft_strdup1(void);
char			*ft_strjoin1(char *s1, char *s2);
bool			ft_strchr1(const char *s, int c);
char			*ft_save(char *s, int c, unsigned int ls);
char			*get_next_line(int fd);
char			*line(int fd, int is_read, unsigned int BF_SIZE);
size_t			ft_strlcpy1(char *d, const char *src, size_t dstsize);
size_t			ft_strlcat1(char *dst, const char *src, size_t dstsize);
char			*ft_substr1(char const *s, unsigned int start, size_t len);
unsigned int	ft_strlen1(const char *s);
int				newline_index(char *buffer);

#endif