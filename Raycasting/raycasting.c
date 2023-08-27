/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:33:52 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/08/27 13:28:33 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_ray_facing_right_dir(double ray_angle)
{
	return (ray_angle < 0.5 * M_PI || ray_angle > 1.5 * M_PI);
}

int	is_ray_facing_left_dir(double ray_angle)
{
	return (!is_ray_facing_right_dir(ray_angle));
}

int	is_ray_facing_down_dir(double ray_angle)
{
	return (ray_angle > 0 && ray_angle < M_PI);
}

int	is_ray_facing_up_dir(double ray_angle)
{
	return (!is_ray_facing_down_dir(ray_angle));
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

void	init_vars_hor(t_map *map, double ray_angle)
{
	map->intersect->next_horz_touch_x = 0;
	map->intersect->next_horz_touch_y = 0;
	map->intersect->horz_wall_hit = false;
	map->intersect->yintercept = floor(map->player->y / map->cube_size) * map->cube_size;
	if (is_ray_facing_down_dir(ray_angle))
		map->intersect->yintercept += map->cube_size;
	map->intersect->xintercept = map->player->x + (map->intersect->yintercept - map->player->y) / tan(ray_angle);
	map->intersect->ystep = map->cube_size;
	if (is_ray_facing_up_dir(ray_angle))
		map->intersect->ystep *= -1;
	map->intersect->xstep = map->cube_size / tan(ray_angle);
	if ((is_ray_facing_left_dir(ray_angle) && map->intersect->xstep > 0)
		|| (is_ray_facing_right_dir(ray_angle) && map->intersect->xstep < 0))
		map->intersect->xstep *= -1;
	map->intersect->next_horz_touch_x = map->intersect->xintercept;
	map->intersect->next_horz_touch_y = map->intersect->yintercept;
}

void	init_vars_ver(t_map *map, double ray_angle)
{
	map->intersect->vert_wall_hit = false;
	map->intersect->xintercept = floor(map->player->x / map->cube_size) * map->cube_size;
	if (is_ray_facing_right_dir(ray_angle))
		map->intersect->xintercept += map->cube_size;
	map->intersect->yintercept = map->player->y + (map->intersect->xintercept - map->player->x) * tan(ray_angle);
	map->intersect->xstep = map->cube_size;
	if (is_ray_facing_left_dir(ray_angle))
		map->intersect->xstep *= -1;
	map->intersect->ystep = map->cube_size * tan(ray_angle);
	if ((is_ray_facing_up_dir(ray_angle) && map->intersect->ystep > 0)
		|| (is_ray_facing_down_dir(ray_angle) && map->intersect->ystep < 0))
		map->intersect->ystep *= -1;
	map->intersect->next_vert_touch_x = map->intersect->xintercept;
	map->intersect->next_vert_touch_y = map->intersect->yintercept;
}

void	vertical_intersections(t_map *map, double ray_angle)
{
	init_vars_ver(map, ray_angle);
	while (map->intersect->next_vert_touch_x >= 0 && map->intersect->next_vert_touch_x <= map->width
		&& map->intersect->next_vert_touch_y >= 0 && map->intersect->next_vert_touch_y <= map->height) {
		if (is_wall(map, map->intersect->next_vert_touch_x - is_ray_facing_left_dir(ray_angle), map->intersect->next_vert_touch_y)) {
			map->intersect->vert_wall_hit = true;
			map->intersect->vert_wall_hit_x = map->intersect->next_vert_touch_x;
			map->intersect->vert_wall_hit_y = map->intersect->next_vert_touch_y;
			break;
		} else {
			map->intersect->next_vert_touch_x += map->intersect->xstep;
			map->intersect->next_vert_touch_y += map->intersect->ystep;
		}
	}
}

void    horizontal_intersections(t_map *map, double ray_angle, int column_id)
{
	(void)column_id;
	init_vars_hor(map, ray_angle);
	while (map->intersect->next_horz_touch_x >= 0 && map->intersect->next_horz_touch_x <= map->width
		&& map->intersect->next_horz_touch_y >= 0 && map->intersect->next_horz_touch_y <= map->height)
	{
		if (is_wall(map, map->intersect->next_horz_touch_x, map->intersect->next_horz_touch_y
			- is_ray_facing_up_dir(ray_angle)))
		{
			map->intersect->horz_wall_hit = true;
			map->intersect->horz_wall_hit_x = map->intersect->next_horz_touch_x;
			map->intersect->horz_wall_hit_y = map->intersect->next_horz_touch_y;
			break ;
		}
		else
		{
			map->intersect->next_horz_touch_x += map->intersect->xstep;
			map->intersect->next_horz_touch_y += map->intersect->ystep;
		}
	}
}

void	distance_calc(t_map *map)
{
	if (map->intersect->horz_wall_hit)
		map->intersect->horz_hit_distance = distanceBetweenPoints(map->player->x, map->player->y
		, map->intersect->horz_wall_hit_x, map->intersect->horz_wall_hit_y);
	else
		map->intersect->horz_hit_distance = INT_MAX;
	if (map->intersect->vert_wall_hit)
		map->intersect->vert_hit_distance = distanceBetweenPoints(map->player->x, map->player->y,
		map->intersect->vert_wall_hit_x, map->intersect->vert_wall_hit_y);
	else
		map->intersect->vert_hit_distance = INT_MAX;
	if (map->intersect->horz_hit_distance < map->intersect->vert_hit_distance)
	{
		map->intersect->wall_hit_x = map->intersect->horz_wall_hit_x;
		map->intersect->wall_hit_y = map->intersect->horz_wall_hit_y;
		map->intersect->distance = map->intersect->horz_hit_distance;
		map->intersect->was_hit_vertic = false;
	}
	else
	{
		map->intersect->wall_hit_x = map->intersect->vert_wall_hit_x;
		map->intersect->wall_hit_y = map->intersect->vert_wall_hit_y;
		map->intersect->distance = map->intersect->vert_hit_distance;
		map->intersect->was_hit_vertic = true;
	}
}

void	cast_ray(t_map *map, double ray_angle)
{
	horizontal_intersections(map, ray_angle, 0);
	vertical_intersections(map, ray_angle);
	distance_calc(map);
}