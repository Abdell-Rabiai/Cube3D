/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:16:42 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/08/29 20:48:27 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

	j = -1;
	if (is_vertic && is_ray_facing_left_dir(map->ray_angle))
		map->offset_x = map->cube_size
			- fmodf(map->intersect->wall_hit_y, map->cube_size);
	else if (is_vertic && is_ray_facing_right_dir(map->ray_angle))
		map->offset_x = fmod(map->intersect->wall_hit_y, map->cube_size);
	else if (!is_vertic && is_ray_facing_down_dir(map->ray_angle))
		map->offset_x = map->cube_size
			- fmodf(map->intersect->wall_hit_x, map->cube_size);
	else
		map->offset_x = fmod(map->intersect->wall_hit_x, map->cube_size);
	map->offset_x = map->offset_x * map->textures[dir].width / map->cube_size;
	while (++j < (int)wallStripHeight)
	{
		map->offset_y = j * map->textures[dir].height / wallStripHeight;
		color = return_my_color(map, map->offset_x, map->offset_y, dir);
		if ((map->start->x > 0 && map->start->x < map->width)
			&& (map->start->y + j > 0 && map->start->y + j < map->height))
			my_mlx_pixel_put(map->image, map->start->x,
				map->start->y + j, color);
	}
}

void	draw_rays(t_map *map)
{
	int				column_id;
	t_directions	dir;

	map->num_rays = map->width;
	map->ray_angle = map->player->rotation_angel - (map->fov_angle / 2);
	dir = 0;
	column_id = -1;
	draw_ceiling_and_floor(map);
	while (++column_id < map->num_rays)
	{
		dir = direction(map, map->ray_angle);
		cast_ray(map, map->ray_angle);
		map->ray_distance = map->intersect->distance * cos(map->ray_angle
				- map->player->rotation_angel);
		map->dist_proj_plane = (map->width / 2) / tan(map->fov_angle / 2);
		map->wall_strip_height = (map->cube_size / map->ray_distance)
			* map->dist_proj_plane;
		map->start->x = column_id;
		map->start->y = (map->height / 2) - (map->wall_strip_height / 2);
		map->end->x = column_id + 1;
		render_wall(map, map->wall_strip_height,
			map->intersect->was_hit_vertic, dir);
		map->ray_angle += map->fov_angle / map->num_rays;
		map->ray_angle = normalize_angle(map->ray_angle);
	}
}
