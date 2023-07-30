/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:33:52 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/07/30 11:56:54 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_ray_facing_right_dir(double rayAngle)
{
	return (rayAngle < 0.5 * PIE || rayAngle > 1.5 * PIE);
}

int	is_ray_facing_left_dir(double rayAngle)
{
	return (!is_ray_facing_right_dir(rayAngle));
}

int	is_ray_facing_down_dir(double rayAngle)
{
	return (rayAngle > 0 && rayAngle < PIE);
}

int	is_ray_facing_up_dir(double rayAngle)
{
	return (!is_ray_facing_down_dir(rayAngle));
}

void draw_line_till_inter(t_map *map, int x1, int y1, int x2, int y2)
{
	map->bresenham->point1.x = x1;
	map->bresenham->point1.y = y1;
	map->bresenham->point2.x = x2;
	map->bresenham->point2.y = y2;
	draw_bresenhams_line(map);
}

double distanceBetweenPoints(double x1, double y1, double x2, double y2)
{
	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

void	init_vars_hor(t_map *map, double rayAngle)
{
	map->intersect->nextHorzTouchX = 0;
	map->intersect->nextHorzTouchY = 0;
	map->intersect->HorzWallHit = false;
	map->intersect->yintercept = floor(map->player->y / SCALE) * SCALE;
	if (is_ray_facing_down_dir(rayAngle))
		map->intersect->yintercept += SCALE;
	map->intersect->xintercept = map->player->x + (map->intersect->yintercept - map->player->y) / tan(rayAngle);
	map->intersect->ystep = SCALE;
	if (is_ray_facing_up_dir(rayAngle))
		map->intersect->ystep *= -1;
	map->intersect->xstep = SCALE / tan(rayAngle);
	if ((is_ray_facing_left_dir(rayAngle) && map->intersect->xstep > 0)
		|| (is_ray_facing_right_dir(rayAngle) && map->intersect->xstep < 0))
		map->intersect->xstep *= -1;
	map->intersect->nextHorzTouchX = map->intersect->xintercept;
	map->intersect->nextHorzTouchY = map->intersect->yintercept;
}

void	init_vars_ver(t_map *map, double rayAngle)
{
	map->intersect->vertWallHit = false;
	map->intersect->xintercept = floor(map->player->x / SCALE) * SCALE;
	if (is_ray_facing_right_dir(rayAngle))
		map->intersect->xintercept += SCALE;
	map->intersect->yintercept = map->player->y + (map->intersect->xintercept - map->player->x) * tan(rayAngle);
	map->intersect->xstep = SCALE;
	if (is_ray_facing_left_dir(rayAngle))
		map->intersect->xstep *= -1;
	map->intersect->ystep = SCALE * tan(rayAngle);
	if ((is_ray_facing_up_dir(rayAngle) && map->intersect->ystep > 0)
		|| (is_ray_facing_down_dir(rayAngle) && map->intersect->ystep < 0))
		map->intersect->ystep *= -1;
	map->intersect->nextVertTouchX = map->intersect->xintercept;
	map->intersect->nextVertTouchY = map->intersect->yintercept;
}

void	vertical_intersections(t_map *map, double rayAngle)
{
	init_vars_ver(map, rayAngle);
	while (map->intersect->nextVertTouchX >= 0 && map->intersect->nextVertTouchX <= map->width && map->intersect->nextVertTouchY >= 0 && map->intersect->nextVertTouchY <= map->height) {
		if (is_there_a_wall(map, map->intersect->nextVertTouchX - is_ray_facing_left_dir(rayAngle), map->intersect->nextVertTouchY)) {
			map->intersect->vertWallHit = true;
			map->intersect->vertWallHitX = map->intersect->nextVertTouchX;
			map->intersect->vertWallHitY = map->intersect->nextVertTouchY;
			break;
		} else {
			map->intersect->nextVertTouchX += map->intersect->xstep;
			map->intersect->nextVertTouchY += map->intersect->ystep;
		}
	}
}

void	distance_calc(t_map *map)
{
	if (map->intersect->HorzWallHit)
		map->intersect->HorzHitDistance = distanceBetweenPoints(map->player->x, map->player->y
		, map->intersect->HorzWallHitX, map->intersect->HorzWallHitY);
	else
		map->intersect->HorzHitDistance = INT_MAX;
	if (map->intersect->vertWallHit)
		map->intersect->vertHitDistance = distanceBetweenPoints(map->player->x, map->player->y,
		map->intersect->vertWallHitX, map->intersect->vertWallHitY);
	else
		map->intersect->vertHitDistance = INT_MAX;
	if (map->intersect->HorzHitDistance < map->intersect->vertHitDistance)
	{
		map->intersect->WallHitX = map->intersect->HorzWallHitX;
		map->intersect->WallHitY = map->intersect->HorzWallHitY;
		map->intersect->distance = map->intersect->HorzHitDistance;
		map->intersect->wasHitVertic = false;
	}
	else
	{
		map->intersect->WallHitX = map->intersect->vertWallHitX;
		map->intersect->WallHitY = map->intersect->vertWallHitY;
		map->intersect->distance = map->intersect->vertHitDistance;
		map->intersect->wasHitVertic = true;
	}
}

void    horizontal_intersections(t_map *map, double rayAngle, int column_id)
{
	init_vars_hor(map, rayAngle);
	while (map->intersect->nextHorzTouchX >= 0 && map->intersect->nextHorzTouchX <= map->width
		&& map->intersect->nextHorzTouchY >= 0 && map->intersect->nextHorzTouchY <= map->height)
	{
		printf("=============================\n");
		printf("nextHorzTouchX column_id = [%f] [%d]\n", map->intersect->nextHorzTouchX, column_id);
		printf("nextHorzTouchY column_id = [%f] [%d]\n", map->intersect->nextHorzTouchY, column_id);
		printf("=============================\n");
		if (is_there_a_wall(map, map->intersect->nextHorzTouchX, map->intersect->nextHorzTouchY
			- is_ray_facing_up_dir(rayAngle)))
		{
			map->intersect->HorzWallHit = true;
			map->intersect->HorzWallHitX = map->intersect->nextHorzTouchX;
			map->intersect->HorzWallHitY = map->intersect->nextHorzTouchY;
			break ;
		}
		else
		{
			map->intersect->nextHorzTouchX += map->intersect->xstep;
			map->intersect->nextHorzTouchY += map->intersect->ystep;
		}
	}
	printf("WallHitX = [%f]\n", map->intersect->WallHitX);
	printf("WallHitY = [%f]\n", map->intersect->WallHitY);
	// draw_line_hor_inter(map, map->player->x, map->player->y, map->intersect->WallHitX, map->intersect->WallHitY);
}

void	cast_ray(t_map *map, double rayAngle)
{
	rayAngle = normalize_angle(rayAngle);
	horizontal_intersections(map, rayAngle, 0);
	vertical_intersections(map, rayAngle);
	distance_calc(map);
}
