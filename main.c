/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:11:30 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/07/21 11:56:14 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

 void all_hooks(t_map *map)
 {
	mlx_hook(map->image->window_ptr, 2, (1L<<0), key_hook, map);
	mlx_hook(map->image->window_ptr, ON_MOUSEMOVE, 0, mouse_hook, map);
	mlx_hook(map->image->window_ptr, 17, 0, exit_hook, 0);
	

	mlx_loop(map->image->mlx_ptr);
 }

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
	t_map *map;
	
	map = malloc(sizeof(t_map));
	initialize_map(map, argv);// this function initializes the map and the player
	if (parsing(argv, argc, map))
		return (1);
	draw_the_map(map);
	mlx_put_image_to_window(map->image->mlx_ptr, map->image->window_ptr, map->image->img, 0, 0);
	all_hooks(map);
	free_map(map);
}
