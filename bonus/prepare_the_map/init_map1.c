/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 13:12:07 by arabiai           #+#    #+#             */
/*   Updated: 2023/08/31 10:25:44 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

size_t	max_len(char **argv)
{
	size_t	max;
	int		map_fd;
	char	*line;

	max = 0;
	map_fd = open(argv[1], O_RDONLY);
	line = get_next_line(map_fd);
	while (line)
	{
		if (line[0] == '1' || line[0] == '0' || line[0] == ' ')
			break ;
		free(line);
		line = get_next_line(map_fd);
	}
	while (line)
	{
		if (ft_strlen(line) > max)
			max = ft_strlen(line) - 1;
		free(line);
		line = get_next_line(map_fd);
	}
	close(map_fd);
	return (max);
}

void	protect(t_map *map)
{
	if (map->cube_size > 19 && map->x)
		map->cube_size = 19;
	if (map->cube_size < 19 && map->x)
		map->cube_size = 19;
	if (map->width < 0)
		map->width = 1;
	if (map->height < 0)
		map->height = 1;
	if (map->width > 5120)
		map->width = 5100;
	if (map->height > 2880)
		map->height = 2800;
	if (map->mini_width < 0)
		map->mini_width *= -1;
	if (map->mini_height < 0)
		map->mini_height *= -1;
	if (map->player->move_speed > 10)
		map->player->move_speed = 2;
	if (map->player->move_speed < 0.1)
		map->player->move_speed = 2;
	if (map->player->rotation_speed > 10)
		map->player->rotation_speed = 0.02;
	if (map->player->rotation_speed < 0.001)
		map->player->rotation_speed = 0.02;
}

int	exit_hook(t_map *map)
{
	mlx_destroy_window(map->mlx_ptr, map->window_ptr);
	free_map(map);
	exit(0);
}
