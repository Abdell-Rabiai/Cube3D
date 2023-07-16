/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:11:30 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/07/16 20:09:22 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parsing(char **argv, int argc, t_map *map)
{
	if (check_file_errors(argv, argc))
		return (1);
	read_textures_colors(map, argv);
	read_map(map, argv);
	if (check_map(map) || check_text(map))
		return (1);
	store_paths_colors(map);
	print_map(map);
	return (0);
}

int main(int argc, char **argv)
{
	t_map map;
	t_mlx_info info;

	initialize_map(&map, &info, argv);
	if (parsing(argv, argc, &map))
		return (1);
	minimap(&map, &info);
	mlx_loop(info.mlx_ptr);
	free_map(&map);
}
