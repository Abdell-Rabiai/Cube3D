/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 06:07:49 by arabiai           #+#    #+#             */
/*   Updated: 2023/08/14 16:37:40 by arabiai          ###   ########.fr       */
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
			max = ft_strlen(line) - 1;
		free(line);
		line = get_next_line(map_fd);
	}
	close(map_fd);
	return (max);
}

void initialize_map(t_map *map, char **argv)
{
	int map_fd;

	map_fd = open(argv[1], O_RDONLY);
	if (map_fd < 0)
	{
		printf("Error, NO sush file exist\n");
		return ;
	}
	map->bresenham = malloc(sizeof(t_bresenham));
	map->image = malloc(sizeof(t_image));
	map->mini_image = malloc(sizeof(t_image));
	map->player = malloc(sizeof(t_player));
	map->intersect = malloc(sizeof(t_intersect));
	map->start = malloc(sizeof(t_cords));
	map->end = malloc(sizeof(t_cords));
	map->start->x = 0;
	map->start->y = 0;
	map->end->x = 0;
	map->end->y = 0;
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

	map->player->x = -1;
	map->player->y = -1;

	map->player->dir = -1;
	map->player->turn_dir = 0;
	map->player->walk_dir = 0;

	map->player->rotation_angel = PIE / 4;

	map->player->move_speed = 11.5;

	map->player->rotation_speed = 0.09;

	map->ceil_color = 0;
	map->floor_color = 0;
	map->text_rows = count_text_lines(argv);
	map->map = NULL;
	map->paths = NULL;
	map->max_len = max_len(argv);
	map->rows = count_map_lines(argv);
	map->cols = count_map_cols(argv);
	map->x = map->max_len;
	map->y = map->rows;
	map->width = (map->max_len * SCALE); //(map->max_len * SCALE);
	map->height = (map->rows * SCALE); //(map->rows * SCALE);
	map->mini_height = 350;
	map->mini_width = 410;
 	
	map->mlx_ptr = mlx_init();
	map->window_ptr = mlx_new_window(map->mlx_ptr, map->width, map->height, "CUBE3D");

	map->image->img = mlx_new_image(map->mlx_ptr, map->width, map->height);
	map->image->addr = mlx_get_data_addr(map->image->img, &map->image->bits_per_pixel, &map->image->line_length, &map->image->endian);

	map->mini_image->img = mlx_new_image(map->mlx_ptr, map->mini_width, map->mini_height);
	map->mini_image->addr = mlx_get_data_addr(map->mini_image->img, &map->mini_image->bits_per_pixel, &map->mini_image->line_length, &map->mini_image->endian);
}
