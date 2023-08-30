/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_errors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:06:55 by arabiai           #+#    #+#             */
/*   Updated: 2023/08/30 17:51:29 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_file_errors(char **argv, int argc)
{
	int	fd;

	if (argc != 2)
		return (printf("Error\nWrong number of arguments\n"), 1);
	else if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
		return (printf("Error\nFile format not correct\n"), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (printf("Error\nFile not found\n"), 1);
	close(fd);
	return (0);
}
