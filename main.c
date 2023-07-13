/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:11:30 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/07/13 13:48:37 by arabiai          ###   ########.fr       */
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

	if (pars_for_errors(argv, argc))
		return (1);
	initialize_map(&map, argv);
	if (read_data(argv, &map))
		return (1);
	if (check_multiple_players(&map))
		return (printf("Error\nMultiple players\n"), 1);
	if (check_is_closed(&map))
		return (printf("Error\nMap is not closed\n"), 1);
	print_map(&map);
	free_map(&map);
	while (1);
}
