/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 06:07:49 by arabiai           #+#    #+#             */
/*   Updated: 2023/07/30 11:35:54 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

size_t max_len(char **argv)
{
	size_t max;
	int map_fd;
	char *line;

	max = 0;
	map_fd = open(argv[1], O_RDONLY);
	line = get_next_line(map_fd);
	while (line)
	{
		if (line[0] == '1' || line[0] == '0' || line[0] == ' ')
			break;
		free(line);
		line = get_next_line(map_fd);
	}
	while (line)
	{
		if (ft_strlen(line) > max)
			max = ft_strlen(line);
		free(line);
		line = get_next_line(map_fd);
	}
	close(map_fd);
	return (max);
}

void initialize_map(t_map *map, char **argv)
{
	// i have three structs in the map struct which are the bresenham, the image, and the player
	map->bresenham = malloc(sizeof(t_bresenham));
	map->image = malloc(sizeof(t_image));
	map->player = malloc(sizeof(t_player));
	map->intersect = malloc(sizeof(t_intersect));
	// initialize the vars of intersect strcut with 0.0 
	map->intersect->WallHitX = 0.0;
	map->intersect->WallHitY = 0.0;
	map->intersect->HorzWallHit = false;
	map->intersect->vertWallHit = false;
	map->intersect->distance = 0.0;
	map->intersect->wasHitVertic = false;
	map->intersect->xintercept = 0.0;
	map->intersect->yintercept = 0.0;
	map->intersect->xstep = 0.0;
	map->intersect->ystep = 0.0;
	map->intersect->HorzWallHitX = 0.0;
	map->intersect->HorzWallHitY = 0.0;
	map->intersect->nextHorzTouchX = 0.0;
	map->intersect->nextHorzTouchY = 0.0;
	map->intersect->nextVertTouchX = 0.0;
	map->intersect->nextVertTouchY = 0.0;
	map->intersect->HorzHitDistance = 0.0;
	map->intersect->vertHitDistance = 0.0;
	map->intersect->vertWallHitX = 0.0;
	map->intersect->vertWallHitY = 0.0;
	map->intersect->vertWallHit = false;

	map->player->x = -1; // the player's initial position is (-1, -1)
	map->player->y = -1;

	map->player->dir = -1; // the player's initial direction is -1
	map->player->turn_dir = 0; // 1 for right or -1 for left i will ue these later in the key_hook function
	map->player->walk_dir = 0; // 1 for forward or -1 for backward 

	map->player->rotation_angel = PIE / 4; // the player's initial rotation angel is 90 degrees
	// the rotation angel is the angle between the player's direction and the X axis
	// when i click the right arrow key the rotation angel increases by ROTATION_SPEED = 0.44 and when i click the left arrow key the rotation angel decreases by 0.44
	// which will make the player's line rotate right or left
	map->player->move_speed = 8.0; // the player's initial move speed is 4
	// the move speed is the distance the player moves in each step, when i click the up arrow key the player moves forward by 4
	// and when i click the down arrow key the player moves backward by 4
	// i will use the move speed later in the key_hook function
	map->player->rotation_speed = 0.2; // the player's initial rotation speed is 0.44 IS how much i will increase or decrease the rotation angel when
	// i click the right or left arrow key
	// i will use the rotation speed later in the key_hook function

	// GO TO THE HOOKS FUNCTION TO SEE HOW I MOVE THE PLAYER AND THE LINE DEPENDING ON THE ROT_ANEL AND THE MOVE SPEED
	/*hado baynin*/
	map->ceil_color = 0;
	map->floor_color = 0;
	map->rows = count_map_lines(argv);
	map->max_len = max_len(argv);
	map->cols = count_map_cols(argv);
	map->text_rows = count_text_lines(argv); // only for the text above the map, map not included
	map->map = NULL;
	map->paths = NULL;
	map->width = map->rows * SCALE; // width of the window = number of columns in the map * SCALE which is 10 (width fo each column in the map is equal to 10 pixels)
	map->height = map->cols * SCALE; // height of the window = number of rows in the map * SCALE which is 10 (height fo each row in the map is equal to 10 pixels)

	// initialize the mlx stuff
	map->image->mlx_ptr = mlx_init();
	map->image->window_ptr = mlx_new_window(map->image->mlx_ptr, map->width, map->height - SCALE, "CUBE3D");
	map->image->img = mlx_new_image(map->image->mlx_ptr, map->width, map->height);
	map->image->addr = mlx_get_data_addr(map->image->img, &map->image->bits_per_pixel, &map->image->line_length, &map->image->endian);

}
