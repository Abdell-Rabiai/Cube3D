/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:11:30 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/08/31 14:08:55 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	all_hooks(t_map *map)
{
	mlx_hook(map->window_ptr, 02, 0L, key_pressed, map);
	mlx_hook(map->window_ptr, 03, 0L, key_released, map);
	mlx_hook(map->window_ptr, 17, 0L, exit_hook, map);
	mlx_loop_hook(map->mlx_ptr, draw_the_frame, map);
}

void	game(t_map *map)
{
	draw_rays(map);
	mlx_put_image_to_window(map->mlx_ptr, map->window_ptr,
		map->image->img, 0, 0);
}

int	main(int argc, char **argv)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	initialize_map(map, argv);
	if (parsing(argv, argc, map))
		return (1);
	get_player_position(map);
	open_textures(map);
	game(map);
	all_hooks(map);
	mlx_loop(map->mlx_ptr);
	free_map(map);
}
