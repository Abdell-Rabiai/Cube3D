/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 06:07:49 by arabiai           #+#    #+#             */
/*   Updated: 2023/09/04 11:40:16 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_malloc(t_map *map, char **argv)
{
	int	map_fd;

	map_fd = open(argv[1], O_RDONLY);
	if (map_fd < 0)
	{
		printf("Error, NO sush file exist\n");
		exit(0);
	}
	map->bresenham = malloc(sizeof(t_bresenham));
	map->image = malloc(sizeof(t_image));
	map->player = malloc(sizeof(t_player));
	map->intersect = malloc(sizeof(t_intersect));
	map->start = malloc(sizeof(t_cords));
	map->end = malloc(sizeof(t_cords));
	map->start->x = 0;
	map->start->y = 0;
	map->end->x = 0;
	map->end->y = 0;
}

void	init_intersect(t_map *map)
{
	map->intersect->wall_hit_x = 0.0;
	map->intersect->wall_hit_y = 0.0;
	map->intersect->horz_wall_hit = false;
	map->intersect->vert_wall_hit = false;
	map->intersect->distance = 0.0;
	map->intersect->was_hit_vertic = false;
	map->intersect->xintercept = 0.0;
	map->intersect->yintercept = 0.0;
	map->intersect->xstep = 0.0;
	map->intersect->ystep = 0.0;
	map->intersect->horz_wall_hit_x = 0.0;
	map->intersect->horz_wall_hit_y = 0.0;
	map->intersect->next_horz_touch_x = 0.0;
	map->intersect->next_horz_touch_y = 0.0;
	map->intersect->next_vert_touch_x = 0.0;
	map->intersect->next_vert_touch_y = 0.0;
	map->intersect->horz_hit_distance = 0.0;
	map->intersect->vert_hit_distance = 0.0;
	map->intersect->vert_wall_hit_x = 0.0;
	map->intersect->vert_wall_hit_y = 0.0;
	map->intersect->vert_wall_hit = false;
}

void	init_player(t_map *map)
{
	map->player->x = -1;
	map->player->y = -1;
	map->player->dir = -1;
	map->player->turn_dir = 0;
	map->player->walk_dir = 0;
	map->player->rotation_angel = M_PI / 4;
	map->player->move_speed = 2.25;
	map->player->rotation_speed = 0.028;
	map->ceil_color = 0;
	map->floor_color = 0;
	map->map = NULL;
	map->paths = NULL;
	map->fov_angle = 60 * (M_PI / 180);
}

void	init_mlx(t_map *map)
{
	map->mlx_ptr = mlx_init();
	if (map->mlx_ptr == NULL)
		exit(0);
	map->window_ptr = mlx_new_window(map->mlx_ptr, map->width,
			map->height, "CUBE3D");
	if (map->window_ptr == NULL)
		exit(0);
	map->image->img = mlx_new_image(map->mlx_ptr, map->width, map->height);
	if (map->image->img == NULL)
	{
		printf("Error\nImage creation failed\n");
		exit(0);
	}
	map->image->addr = mlx_get_data_addr(map->image->img,
			&map->image->bits_per_pixel, &map->image->line_length,
			&map->image->endian);
	if (map->image->addr == NULL)
	{
		printf("Error\nImage creation failed\n");
		exit(0);
	}
}

void	initialize_map(t_map *map, char **argv)
{
	init_malloc(map, argv);
	init_intersect(map);
	init_player(map);
	map->text_rows = count_text_lines(argv);
	map->max_len = max_len(argv);
	map->rows = count_map_lines(argv);
	map->cols = count_map_cols(argv);
	map->x = map->max_len;
	map->y = map->rows;
	map->width = 1600;
	map->height = 900;
	map->cube_size = 19;
	protect(map);
	init_mlx(map);
}
