/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdell_rabiai <abdell_rabiai@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:11:30 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/07/10 18:28:58 by abdell_rabi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_map *map)
{
	int	i;

	i = -1;
	while (++i < 4)
		free(map->paths[i]);
	free(map->paths);
	i = -1;
	while (++i < map->rows)
		free(map->map[i]);
	free(map->map);
}

int main(int argc, char **argv)
{
	int		map_fd;
	t_map	map;

	if (argc != 2)
		return (1);
	map.ceil_color = 0;
	map.floor_color = 0;
	map_fd = open(argv[1], O_RDONLY);
	map.rows = count_map_lines(map_fd);
	printf("ROWS {%d}\n", map.rows);
	map_fd = open(argv[1], O_RDONLY);
	if (pars_map(map_fd, &map))
		return (1);
	free_map(&map);
	// while (true);
}
