/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:16:42 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/08/27 13:37:17 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rect(t_map *map, int x, int y, double height, int color)
{
	int	j;

	j = -1;
	while (++j < height)
	{
		if ((x > 0 && x < map->width)
			&& (y + j > 0 && y + j < map->height))
			my_mlx_pixel_put(map->image, x, y + j, color);
	}
}

int	return_my_color(t_map *map, double of_x, double of_y, int dir)
{
	char	*data;
	int		index;

	index = (floor(of_y) * map->textures[dir].line_length) + (floor(of_x) * 4);
	if (index < 0 || index >= map->textures[dir].width
		* map->textures[dir].height * 4)
		return (0);
	data = map->textures[dir].addr + index;
	return (*(unsigned int *)data);
}

void	render_wall(t_map *map, double wallStripHeight, bool is_vertic, int dir)
{
	int		j;
	int		color;
	double	offset_x;
	double	offset_y;

	j = -1;
	if (is_vertic && is_ray_facing_left_dir(map->ray_angle))
		offset_x = map->cube_size - fmodf(map->intersect->wall_hit_y, map->cube_size);
	else if (is_vertic && is_ray_facing_right_dir(map->ray_angle))
		offset_x = fmod(map->intersect->wall_hit_y, map->cube_size);
	else if (!is_vertic && is_ray_facing_down_dir(map->ray_angle))
		offset_x = map->cube_size - fmodf(map->intersect->wall_hit_x, map->cube_size);
	else
		offset_x = fmod(map->intersect->wall_hit_x, map->cube_size);
	offset_x = offset_x * map->textures[dir].width / map->cube_size;
	while (++j < (int)wallStripHeight)
	{
		offset_y = j * map->textures[dir].height / wallStripHeight;
		color = return_my_color(map, offset_x, offset_y, dir);
		if ((map->start->x > 0 && map->start->x < map->width)
			&& (map->start->y + j > 0 && map->start->y + j < map->height))
			my_mlx_pixel_put(map->image, map->start->x, map->start->y + j, color);
	}
}

void	draw_rays(t_map *map)
{
	double FOV_ANGLE = 60 * (M_PI / 180);
	int num_rays = map->width; // number of rays map->x * map->cube_size
	map->ray_angle = map->player->rotation_angel - (FOV_ANGLE / 2);
	int column_id = -1;
	t_directions	dir;
	double	wallStripHeight;
	double	distanceProjectionPlane;
	double	ray_distance;
	dir = 0;
	draw_ceiling_and_floor(map);
	while (++column_id < num_rays)
	{
		dir = direction(map, map->ray_angle);
		cast_ray(map, map->ray_angle);
		ray_distance = map->intersect->distance * cos(map->ray_angle - map->player->rotation_angel);
		distanceProjectionPlane = (map->width / 2) / tan(FOV_ANGLE / 2);
		wallStripHeight = (map->cube_size / ray_distance) * distanceProjectionPlane;
		map->start->x = column_id;
		map->start->y = (map->height / 2) - (wallStripHeight / 2);
		map->end->x = column_id + 1;
		map->end->y = wallStripHeight < map->height ? wallStripHeight : map->height;
		render_wall(map, wallStripHeight, map->intersect->was_hit_vertic, dir);
		map->ray_angle += FOV_ANGLE / num_rays;
		map->ray_angle = normalize_angle(map->ray_angle);
	}
}
 