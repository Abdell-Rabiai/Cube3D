/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 06:07:49 by arabiai           #+#    #+#             */
/*   Updated: 2023/07/21 12:03:16 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void initialize_map(t_map *map, char **argv)
{
	// i have three structs in the map struct which are the bresenham, the image, and the player
	map->bresenham = malloc(sizeof(t_bresenham));
	map->image = malloc(sizeof(t_image));
	map->player = malloc(sizeof(t_player));

	map->player->x = -1; // the player's initial position is (-1, -1)
	map->player->y = -1;

	map->player->dir = -1; // the player's initial direction is -1
	map->player->turn_dir = 0; // 1 for right or -1 for left i will ue these later in the key_hook function
	map->player->walk_dir = 0; // 1 for forward or -1 for backward 
	
	map->player->rotation_angel = PIE / 2; // the player's initial rotation angel is 90 degrees
	// the rotation angel is the angle between the player's direction and the X axis
	// when i click the right arrow key the rotation angel increases by ROTATION_SPEED = 0.44 and when i click the left arrow key the rotation angel decreases by 0.44
	// which will make the player's line rotate right or left
	map->player->move_speed = 4.0; // the player's initial move speed is 4
	// the move speed is the distance the player moves in each step, when i click the up arrow key the player moves forward by 4
	// and when i click the down arrow key the player moves backward by 4
	// i will use the move speed later in the key_hook function
	map->player->rotation_speed = 0.44; // the player's initial rotation speed is 0.44 IS how much i will increase or decrease the rotation angel when
	// i click the right or left arrow key
	// i will use the rotation speed later in the key_hook function

	// GO TO THE HOOKS FUNCTION TO SEE HOW I MOVE THE PLAYER AND THE LINE DEPENDING ON THE ROT_ANEL AND THE MOVE SPEED
	/*hado baynin*/
	map->ceil_color = 0;
	map->floor_color = 0;
	map->rows = count_map_lines(argv);
	map->cols = count_map_cols(argv);
	map->text_rows = count_text_lines(argv); // only for the text above the map, map not included
	map->map = NULL;
	map->paths = NULL;
	map->width = map->cols * SCALE; // width of the window = number of columns in the map * SCALE which is 10 (width fo each column in the map is equal to 10 pixels)
	map->height = map->rows * SCALE; // height of the window = number of rows in the map * SCALE which is 10 (height fo each row in the map is equal to 10 pixels)

	// initialize the mlx stuff
	map->image->mlx_ptr = mlx_init();
	map->image->window_ptr = mlx_new_window(map->image->mlx_ptr, map->height, map->width, "CUBE3D");
	map->image->img = mlx_new_image(map->image->mlx_ptr, map->height, map->width);
	map->image->addr = mlx_get_data_addr(map->image->img, &map->image->bits_per_pixel, &map->image->line_length, &map->image->endian);

}
