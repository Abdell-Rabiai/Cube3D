/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 06:06:13 by arabiai           #+#    #+#             */
/*   Updated: 2023/07/21 12:37:58 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	exit_hook(void)
{
	exit(0);
}

void apply_the_changes(t_map *map) // this function applies the changed values (walk_dir and turn_dir) gotten from the key_hook function to the player's position and rotation angel
{
	t_player *player; // i intiate a player pointer to the player struct in the map struct
	int transaltion_distance; // this is the distance the player will move in each step (how much i should add to the player's x and y in each step)
	// its like translate a line a certain distance
	

	player = map->player;
	transaltion_distance = player->walk_dir * player->move_speed; // the translation distance is literraly (move_speed==4 in init) but i multiply it by walk_dir to make the player move forward or backward
	// and walk_dir is 1 or -1. meaning this distance will either increase or decrease with 4 steps
	// now that we know the distance we should add to the player's x and y we can calculate the new x and y of the player
	// keep in mind that we only change the x and y of the player when the walk_dir is not 0 beacuse if it is 0 the player will not move (translation distnace in this case will be 0)
	player->rotation_angel += player->turn_dir * player->rotation_speed; // the rotation angel is literraly (rotation_speed==0.44 in init) but i multiply it by turn_dir to make the player rotate right or left
	// and turn_dir is 1 or -1. meaning this angel will either increase or decrease with 0.44 steps
	// now that we know the rotation angel we should change the x and y of the player
	// keep in mind that we only change the x and y of the player when the turn_dir is not 0 beacuse if it is 0 the player will not rotate (rotation_angel in this case will be 0)
	
	// now we can calculate the new x and y of the player
	player->x += transaltion_distance * cos(player->rotation_angel); // the new x of the player is the old x + the translation distance * cos(rotation_angel)
	// imagine a triangle with the hypotenuse = translation_distance and the angle between the hypotenuse and the x axis = rotation_angel
	player->y += transaltion_distance * sin(player->rotation_angel); // the new y of the player is the old y + the translation distance * sin(rotation_angel)
	//CHECK THE PAPER ON THE TABLE TO SEE HOW I GOT THESE FORMULAS
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
