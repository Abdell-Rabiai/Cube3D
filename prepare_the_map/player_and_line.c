/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_and_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 06:02:45 by arabiai           #+#    #+#             */
/*   Updated: 2023/08/03 15:40:10 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void draw_line(t_map *map, int x1, int y1)
{
	map->bresenham->point1.x = x1;
	map->bresenham->point1.y = y1;
	map->bresenham->point2.x = x1 + (30 * cos(map->player->rotation_angel));
	map->bresenham->point2.y = y1 + (30 * sin(map->player->rotation_angel));
	draw_bresenhams_line(map);
}

void draw_the_player(t_map *map) 
{
	draw_circle(map, map->player->x, map->player->y, 4, 0x228811);
	draw_line(map, map->player->x, map->player->y); 
}

int draw_the_map(t_map *map)
{
	minimap(map);
	draw_the_player(map);
	return (0);
}

void	initialize_bresenhams_variables(t_bresenham *map)
{
	map->dx = abs(map->point2.x - map->point1.x);
	map->dy = -abs(map->point2.y - map->point1.y);
	if (map->point1.x < map->point2.x)
		map->step_x = 1;
	else
		map->step_x = -1;
	if (map->point1.y < map->point2.y)
		map->step_y = 1;
	else
		map->step_y = -1;
	map->err = map->dx + map->dy;
}

void	draw_bresenhams_line(t_map *carte) 
{
	t_bresenham *map;
	t_image *image;

	map = carte->bresenham;
	image = carte->image;
	initialize_bresenhams_variables(map);
	while (1)
	{
		if ((map->point1.x > 0 && map->point1.x < carte->width)
			&& (map->point1.y > 0 && map->point1.y < carte->height))
			my_mlx_pixel_put(image, map->point1.x, map->point1.y, 0x228811);
		if (map->point1.x == map->point2.x
			&& map->point1.y == map->point2.y)
			break ;
		map->e2 = 2 * map->err;
		if (map->e2 >= map->dy)
		{
			map->err = map->err + map->dy;
			map->point1.x = map->point1.x + map->step_x;
		}
		else if (map->e2 <= map->dx)
		{
			map->err = map->err + map->dx;
			map->point1.y = map->point1.y + map->step_y;
		}
	}
}
