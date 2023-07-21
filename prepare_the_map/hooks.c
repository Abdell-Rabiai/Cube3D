/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 06:06:13 by arabiai           #+#    #+#             */
/*   Updated: 2023/07/21 06:15:29 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	exit_hook(void)
{
	exit(0);
}

void apply_the_changes(t_map *map)
{
	t_player *player;
	int transaltion_distance;
	

	player = map->player;
	player->rotation_angel += player->turn_dir * player->rotation_speed;
	
	transaltion_distance = player->walk_dir * player->move_speed;
	player->x += transaltion_distance * cos(player->rotation_angel);
	player->y += transaltion_distance * sin(player->rotation_angel);
}

void change_coordinates(t_map *map, int x2, int y2)
{
	t_player *player;
	int x1;
	int y1;
	
	player = map->player; 
	x1 = player->x;
	y1 = player->y;
	player->x = x2;
	player->y = y2;

	// modify the rotaion angel to make the line follow the direction of the mouse
	player->rotation_angel = atan2((y2 - y1), (x2 - x1));
}

void create_new_image(t_map *map, t_image *image)
{
    mlx_destroy_image(image->mlx_ptr, image->img);
	mlx_clear_window(image->mlx_ptr, image->window_ptr);
	image->img = mlx_new_image(image->mlx_ptr, map->height, map->width);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel, &image->line_length, &image->endian);
}

int	mouse_hook(int x, int y, t_map *map)
{
	t_image *image;
	
	image = map->image;
	
	printf("x = %d\n", x);
	printf("y = %d\n", y);
	
	create_new_image(map, image);
	change_coordinates(map, x, y);
	draw_the_map(map);
	mlx_put_image_to_window(image->mlx_ptr, image->window_ptr, image->img, 0, 0);
	return (0);
}

void player_movement_hooks(int keycode, t_map *map)
{
    if (keycode == 126) // up forward
	{
		map->player->walk_dir = 1;
		map->player->turn_dir = 0;
	}
	else if (keycode == 125)
	{
		map->player->walk_dir = -1; // down backword
		map->player->turn_dir = 0;
	}
	else if (keycode == 124) // right turnright
	{
		map->player->turn_dir = 1;
		map->player->walk_dir = 0;
	}
	else if (keycode == 123) // left turnleft
	{
		map->player->turn_dir = -1;
		map->player->walk_dir = 0;
	}
}

int	key_hook(int keycode, t_map *map)
{
	t_image *image;
	
	image = map->image;
	printf("keycode = %d\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_window(map->image->mlx_ptr, map->image->window_ptr);
		map->image->window_ptr = NULL;
		exit(0);
	}
	player_movement_hooks(keycode, map);
	create_new_image(map, image);
	apply_the_changes(map);
	draw_the_map(map);
	mlx_put_image_to_window(image->mlx_ptr, image->window_ptr, image->img, 0, 0);
	return (0);
}
