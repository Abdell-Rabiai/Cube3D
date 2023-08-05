/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:16:42 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/08/05 14:48:32 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// # define FOV_ANGLE = 60 * (PIE / 180)
// # define WALL_STRIP_WIDTH = 1;

void draw_line_rays(t_map *map, int x1, int y1, double rayAngle)
{
	map->bresenham->point1.x = x1;
	map->bresenham->point1.y = y1;
	map->bresenham->point2.x = x1 + (30 * cos(rayAngle));
	map->bresenham->point2.y = y1 + (30 * sin(rayAngle));
	draw_bresenhams_line(map);
}

//write a function that will draw a rectangle like rect func in js:
void rect(t_map *map, int x, int y, double width, double height)
{
	int i;
	int j;
    (void)width;

	i = 0;
    j = -1;
    while (++j < height)
    {
        if ((x + i > 0 && x + i < map->width)
            && (y + j > 0 && y + j < map->height))
            my_mlx_pixel_put(map->image, x + i, y + j, 0xFFF099);
    }
}

void    draw_rays(t_map *map)
{
    double FOV_ANGLE = 60 * (PIE / 180);
    int num_rays = map->max_len * SCALE;
    double rayAngle = map->player->rotation_angel - (FOV_ANGLE / 2);
    int column_id = -1;

    double wallStripHeight;
	double distanceProjectionPlane;
	while (++column_id < num_rays)
	{
		cast_ray(map, rayAngle);
		distanceProjectionPlane = (map->width / 2) / tan(FOV_ANGLE / 2);
		wallStripHeight = (SCALE / map->intersect->distance) * distanceProjectionPlane;
        // draw_line_rays(map, map->player->x, map->player->y, rayAngle);
		rect(map, column_id, (map->height / 2) - (wallStripHeight / 2), 1, wallStripHeight);
		printf("%f\n", (map->height / 2) - (wallStripHeight / 2));
		rayAngle += FOV_ANGLE / num_rays;
	}
}
 