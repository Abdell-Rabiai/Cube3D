/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 06:07:49 by arabiai           #+#    #+#             */
/*   Updated: 2023/07/21 06:17:18 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void initialize_map(t_map *map, char **argv)
{
	
	map->bresenham = malloc(sizeof(t_bresenham));
	map->image = malloc(sizeof(t_image));
	map->player = malloc(sizeof(t_player));

	map->player->x = -1;
	map->player->y = -1;
	map->player->dir = -1;
	map->player->turn_dir = 0; // 1 for right or -1 for left
	map->player->walk_dir = 0; // 1 for forward or -1 for backward
	map->player->rotation_angel = PIE / 2;
	map->player->move_speed = 4.0; // PIXELS PER FRAME
	map->player->rotation_speed = 0.44; // ANGELS PER FRAME

	map->ceil_color = 0;
	map->floor_color = 0;
	map->rows = count_map_lines(argv);
	map->cols = count_map_cols(argv);
	map->text_rows = count_text_lines(argv);
	map->map = NULL;
	map->paths = NULL;
	map->width = map->cols * SCALE;
	map->height = map->rows * SCALE;

	map->image->mlx_ptr = mlx_init();
	map->image->window_ptr = mlx_new_window(map->image->mlx_ptr, map->height, map->width, "CUBE3D");
	map->image->img = mlx_new_image(map->image->mlx_ptr, map->height, map->width);
	map->image->addr = mlx_get_data_addr(map->image->img, &map->image->bits_per_pixel, &map->image->line_length, &map->image->endian);

}
