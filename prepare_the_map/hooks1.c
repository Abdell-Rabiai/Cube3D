/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 13:12:58 by arabiai           #+#    #+#             */
/*   Updated: 2023/08/30 18:30:19 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	create_new_image(t_map *map, t_image *image)
{
	mlx_destroy_image(map->mlx_ptr, image->img);
	mlx_destroy_image(map->mlx_ptr, map->mini_image->img);
	mlx_clear_window(map->mlx_ptr, map->window_ptr);
	image->img = mlx_new_image(map->mlx_ptr, map->width, map->height);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel,
			&image->line_length, &image->endian);
	map->mini_image->img = mlx_new_image(map->mlx_ptr,
			map->mini_width, map->mini_height);
	map->mini_image->addr = mlx_get_data_addr(map->mini_image->img,
			&map->mini_image->bits_per_pixel,
			&map->mini_image->line_length, &map->mini_image->endian);
}

int	mouse_hook(int x, int y, t_map *map)
{
	t_image	*image;

	image = map->image;
	create_new_image(map, image);
	change_coordinates(map, x, y);
	game(map);
	return (0);
}

int	key_released(int keycode, t_map *map)
{
	if (keycode == 13 || keycode == 126)
		map->player->walk_dir = 0;
	else if (keycode == 1 || keycode == 125)
		map->player->walk_dir = 0;
	else if (keycode == 124)
		map->player->turn_dir = 0;
	else if (keycode == 123)
		map->player->turn_dir = 0;
	else if (keycode == 2 || keycode == 0)
		map->player->translate_y = 0;
	else if (keycode == 53)
	{
		mlx_destroy_window(map->mlx_ptr, map->window_ptr);
		free_map(map);
		exit(0);
	}
	return (0);
}

int	key_pressed(int keycode, t_map *map)
{
	if (keycode == 53)
	{
		mlx_destroy_image(map->mlx_ptr, map->image->img);
		mlx_destroy_image(map->mlx_ptr, map->mini_image->img);
		mlx_destroy_window(map->mlx_ptr, map->window_ptr);
		free_map(map);
		exit(0);
	}
	if (keycode == 13 || keycode == 126)
		map->player->walk_dir = 1;
	else if (keycode == 1 || keycode == 125)
		map->player->walk_dir = -1;
	else if (keycode == 2)
		map->player->translate_y = 1;
	else if (keycode == 124)
		map->player->turn_dir = 1;
	else if (keycode == 0)
		map->player->translate_y = -1;
	else if (keycode == 123)
		map->player->turn_dir = -1;
	return (0);
}

int	draw_the_frame(t_map *map)
{
	t_image	*image;

	image = map->image;
	create_new_image(map, image);
	apply_the_changes(map);
	game(map);
	return (0);
}
