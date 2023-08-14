/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 06:06:13 by arabiai           #+#    #+#             */
/*   Updated: 2023/08/14 20:19:47 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	exit_hook(t_map *map)
{
	mlx_destroy_window(map->mlx_ptr, map->window_ptr);
	free_map(map);
	exit(0);
}

int is_there_a_wall(t_map *map, double x, double y)
{
	int x0;
	int y0;
	
	// if (x < 0 || x > map->width - 1 || y < 0 || y > map->height - 1)
	// 	return (-1);
	x0 = floor(x / SCALE);
	y0 = floor(y / SCALE);
	if (x0 < 0 || x0 > map->x - 1 || y0 < 0 || y0 > map->y - 1)
		return (-1);
	// printf("(%d, %d)\n", x0, y0);
	if (map->map[y0][x0] == '1' || map->map[y0][x0] == ' ')
		return (1);
	else
		return (0);
}

void apply_the_changes(t_map *map)
{
	t_player	*player; 
	double			new_player_x;
	double			new_player_y;
	double			transaltion_distance;

	player = map->player;
	transaltion_distance = player->walk_dir * player->move_speed;
	player->rotation_angel += player->turn_dir * player->rotation_speed; 
	player->rotation_angel = normalize_angle(player->rotation_angel);

	new_player_x = player->x + transaltion_distance * cos(player->rotation_angel);
	new_player_y = player->y + transaltion_distance * sin(player->rotation_angel);
	
	if (!is_there_a_wall(map, (int)new_player_x, (int)new_player_y))
	{
		player->x = new_player_x;
		player->y = new_player_y;
	}
}

void change_coordinates(t_map *map, int x2, int y2)
{
	t_player	*player;
	int			x1;
	int			y1;

	player = map->player;
	x1 = player->x;
	y1 = player->y;
	if (x2 < 0 || x2 > map->width - 1 || y2 < 0 || y2 > map->height - 1)
		return ;
	if (x2 > player->previous_x)
		player->rotation_angel += player->rotation_speed / 3;
	else
		player->rotation_angel -= player->rotation_speed / 3;
	player->previous_x = x2;
	player->previous_y = y2;
}

void create_new_image(t_map *map, t_image *image)
{
    mlx_destroy_image(map->mlx_ptr, image->img);
	mlx_destroy_image(map->mlx_ptr, map->mini_image->img);
	mlx_clear_window(map->mlx_ptr, map->window_ptr);
	image->img = mlx_new_image(map->mlx_ptr, map->width, map->height);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel, &image->line_length, &image->endian);
	map->mini_image->img = mlx_new_image(map->mlx_ptr, map->mini_width, map->mini_height);
	map->mini_image->addr = mlx_get_data_addr(map->mini_image->img, &map->mini_image->bits_per_pixel, &map->mini_image->line_length, &map->mini_image->endian);
}

int	mouse_hook(int x, int y, t_map *map)
{
	t_image *image;
	
	image = map->image;
	create_new_image(map, image);
	change_coordinates(map, x, y);
	
	game(map);
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
	// printf("keycode = %d\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_window(map->mlx_ptr, map->window_ptr);
		free_map(map);
		exit(0);
	}
	player_movement_hooks(keycode, map);
	create_new_image(map, image);
	apply_the_changes(map);
	
	game(map);
	return (0);
}
