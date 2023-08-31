/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:33:52 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/08/30 18:50:51 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	distance_calc(t_map *map)
{
	if (map->intersect->horz_wall_hit)
		map->intersect->horz_hit_distance
			= dist_be2n_pts(map->player->x, map->player->y,
				map->intersect->horz_wall_hit_x,
				map->intersect->horz_wall_hit_y);
	else
		map->intersect->horz_hit_distance = INT_MAX;
	if (map->intersect->vert_wall_hit)
		map->intersect->vert_hit_distance
			= dist_be2n_pts(map->player->x, map->player->y,
				map->intersect->vert_wall_hit_x,
				map->intersect->vert_wall_hit_y);
	else
		map->intersect->vert_hit_distance = INT_MAX;
	assign_wall_hit_cords(map, map->intersect->vert_hit_distance
		< map->intersect->horz_hit_distance);
}

void	cast_ray(t_map *map, double ray_angle)
{
	horizontal_intersections(map, ray_angle);
	vertical_intersections(map, ray_angle);
	distance_calc(map);
}
