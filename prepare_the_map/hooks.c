/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 06:06:13 by arabiai           #+#    #+#             */
/*   Updated: 2023/08/04 15:54:37 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	exit_hook(t_map *map)
{
	mlx_destroy_window(map->mlx_ptr, map->window_ptr);
	free_map(map);
	exit(0);
}

int is_there_a_wall(t_map *map, int x, int y)
{
	int x0;
	int y0;
	
	if (x < 0 || x > map->width - 1 || y < 0 || y > map->height - 1)
		return (0);
	x0 = x / SCALE;
	y0 = y / SCALE;
	if (map->map[y0][x0] == '1' || map->map[y0][x0] == ' ')
		return (1);
	else
		return (0);
}

void apply_the_changes(t_map *map)
{
	t_player	*player; 
	int			new_player_x;
	int			new_player_y;
	int			transaltion_distance;

	player = map->player;
	transaltion_distance = player->walk_dir * player->move_speed;
	player->rotation_angel += player->turn_dir * player->rotation_speed; 

	new_player_x = player->x + transaltion_distance * cos(player->rotation_angel);
	new_player_y = player->y + transaltion_distance * sin(player->rotation_angel);
	
	if (!is_there_a_wall(map, new_player_x, new_player_y))
	{
		player->x = new_player_x;
		player->y = new_player_y;
	}
}

void change_coordinates(t_map *map, int x2, int y2)
{
	t_player *player;
	int x1;
	int y1;

	player = map->player;
	x1 = player->x;
	y1 = player->y;
	if (x2 < 0 || x2 > map->width - 1 || y2 < 0 || y2 > map->height - 1)
		return ;
	if (!is_there_a_wall(map, x2, y2))
	{
		player->x = x2;
		player->y = y2;
		player->rotation_angel = atan2((y2 - y1), (x2 - x1));
	}
}

void create_new_image(t_map *map, t_image *image)
{
    mlx_destroy_image(map->mlx_ptr, image->img);
	mlx_clear_window(map->mlx_ptr, map->window_ptr);
	image->img = mlx_new_image(map->mlx_ptr, map->width, map->height);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel, &image->line_length, &image->endian);
}

int	mouse_hook(int x, int y, t_map *map)
{
	t_image *image;
	
	image = map->image;
	create_new_image(map, image);
	change_coordinates(map, x, y);
	draw_the_map(map);
	
	draw_rays(map);
	mlx_put_image_to_window(map->mlx_ptr, map->window_ptr, image->img, 0, 0);
	return (0);
}

void player_movement_hooks(int keycode, t_map *map)
{
    if (keycode == 126) // up == forward
	{
		map->player->walk_dir = 1;// id walk_dir == 1 the player moves forward in apply_the_changes function
		map->player->turn_dir = 0; // i should set the turn_dir to 0 because if i don't the player will rotate while moving forward
	}
	else if (keycode == 125)  // down == backword
	{
		map->player->walk_dir = -1; // if walk_dir == -1 the player moves backward in apply_the_changes function
		map->player->turn_dir = 0; // same here he will rotate while moving backward if i don't set turn_dir to 0
	}
	else if (keycode == 124) // right == turnright
	{
		map->player->turn_dir = 1; // if turn_dir == 1 the player rotates right in apply_the_changes function
		map->player->walk_dir = 0; // same here he will move forward while rotating if i don't set walk_dir to 0
	}
	else if (keycode == 123) // left == turnleft
	{
		map->player->turn_dir = -1; // if turn_dir == -1 the player rotates left in apply_the_changes function
		map->player->walk_dir = 0; // same here he will move forward while rotating if i don't set walk_dir to 0
	}
	//GO TO APPLY_THE_CHANGES  TO SEE HOW I USE THESE WALK_DIR AND TURN_DIR VARIABLES TO MOVE THE PLAYER AND THE LINE
}

int	key_hook(int keycode, t_map *map)
{
	t_image *image;
	
	image = map->image;
	printf("keycode = %d\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_window(map->mlx_ptr, map->window_ptr);
		free_map(map);
		exit(0);
	}
	player_movement_hooks(keycode, map);
	create_new_image(map, image);
	apply_the_changes(map);
	draw_the_map(map);
	draw_rays(map);
	mlx_put_image_to_window(map->mlx_ptr, map->window_ptr, image->img, 0, 0);
	return (0);
}
