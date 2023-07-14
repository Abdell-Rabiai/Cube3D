/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:11:30 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/07/14 13:27:25 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
	t_map map;
	t_mlx_info info;

	info.mlx_ptr = mlx_init();
	initialize_map(&map, argv);
	if (check_file_errors(argv, argc))
		return (1);
	read_textures_colors(&map, argv);
	read_map(&map, argv);
	if (check_map(&map) || check_text(&map))
		return (1);
	// if everything is ok store map and text and print everything
	store_paths_colors(&map);
	print_map(&map);
	info.window_ptr = mlx_new_window(info.mlx_ptr, map.rows * SCALE, 33 * SCALE, "cub3d");
	minimap(&map, &info);
	// free_map(&map);
	mlx_loop(info.mlx_ptr);
	// start_the_game(&map);
	free_map(&map);
	// while (1);
}
