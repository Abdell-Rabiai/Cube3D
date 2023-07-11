/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:11:30 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/07/11 08:30:30 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void initialize_map(t_map *map, char **argv)
{
	map->ceil_color = 0;
	map->floor_color = 0;
	map->rows = count_map_lines(argv);
	map->map = NULL;
	map->paths = NULL;
}

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
	t_map	map;

	if (argc != 2)
		return (1);
	initialize_map(&map, argv);
	if (read_data(argv, &map))
		return (1);
	if (pars_for_errors(&map))
		return (1);
	free_map(&map);
	while (1);
}
