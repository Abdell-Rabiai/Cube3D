/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:16:42 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/07/29 14:34:28 by ahmaymou         ###   ########.fr       */
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

void    draw_rays(t_map *map)
{
    double FOV_ANGLE = 60 * (PIE / 180);
    int num_rays = map->cols * SCALE;
    double rayAngle = map->player->rotation_angel - (FOV_ANGLE / 2);
    int column_id = -1;

    while (++column_id < num_rays)
    {
        // draw_line_rays(map, map->player->x, map->player->y, rayAngle);
        cast_ray(map, rayAngle);
        draw_line_till_inter(map, map->player->x, map->player->y, map->intersect->WallHitX, map->intersect->WallHitY);
        rayAngle += FOV_ANGLE / num_rays;
    }
}
 