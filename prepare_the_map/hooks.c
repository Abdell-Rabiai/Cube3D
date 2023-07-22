/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 06:06:13 by arabiai           #+#    #+#             */
/*   Updated: 2023/07/22 04:46:18 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	exit_hook(void)
{
	exit(0);
}

int is_there_a_wall(t_map *map, int x, int y)
{
	int x0; // x0 and y0 are the coordinates of the square that the player is in
	int y0; // the indexes in the matrix (map->map)
	
	x0 = x / SCALE; // i divide by SCALE to get the coordinates of the square that the player is in
	y0 = y / SCALE;
	if (x0 < 0 || x0 > map->width || y0 < 0 || y0 > map->height)
		return (1);
	printf("x0 = [%d]\n", x0);
	printf("y0 = [%d]\n", y0);
	printf("map->map[x0][y0] = [%c]\n", map->map[x0][y0]);
	// if the player is in a wall then return 1 else return 0
	if (map->map[x0][y0] == '1') 
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
	
	// if the new player coordinates are not in a wall then we can move the player
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
	// old coordinates
	x1 = player->x;
	y1 = player->y;
	if (!is_there_a_wall(map, x2, y2))
	{
		// new coordinates
		player->x = x2;
		player->y = y2;
		// modify the rotaion angel to make the line follow the direction of the mouse
		player->rotation_angel = atan2((y2 - y1), (x2 - x1));
	}
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
	
	// printf("x = %d\n", x);
	// printf("y = %d\n", y);
	
	create_new_image(map, image);
	change_coordinates(map, x, y);
	draw_the_map(map);
	mlx_put_image_to_window(image->mlx_ptr, image->window_ptr, image->img, 0, 0);
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
