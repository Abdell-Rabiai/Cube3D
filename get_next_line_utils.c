/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:18:11 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/01/03 12:45:27 by ahmaymou        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

unsigned int	ft_strlen1(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i])
		i++;
	return ((unsigned int)i);
}

int	newline_index(char	*buff)
{
	int	i;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	return (i + 1);
}

bool	ft_strchr1(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (false);
	while (s[i])
	{
		if (s[i] == c)
			return (true);
	i++;
	}
	return (false);
}

char	*ft_save(char *s, int c, unsigned int ls)
{
	char	*s1;

	s1 = ft_substr1(s, c, ls - c + 1);
	free(s);
	return (s1);
}

char	*line(int fd, int is_read, unsigned int BF_SIZE)
{
	static char	*buffer;
	char		*line;
	char		buff[BF_SIZE + 1];

	while (is_read && !ft_strchr1(buffer, '\n'))
	{
		is_read = read(fd, buff, BF_SIZE);
		if (is_read < 0)
		{
			free(buffer);
			buffer = NULL;
			return (NULL);
		}
		if (!buffer)
			buffer = ft_strdup1();
		buff[is_read] = '\0';
		buffer = ft_strjoin1(buffer, buff);
	}
	if (!buffer && !is_read)
		return (NULL);
	line = ft_substr1(buffer, 0, newline_index(buffer));
	buffer = ft_save(buffer, newline_index(buffer), ft_strlen1(buffer));
	return (line);
}
