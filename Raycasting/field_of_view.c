/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_of_view.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 12:08:27 by arabiai           #+#    #+#             */
/*   Updated: 2023/08/27 12:25:47 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	rgba_to_int(int r, int g, int b, double a)
{
	return ((int)(a * 255) << 24 | r << 16 | g << 8 | b);
}

void	*open_texture_files(t_map *map, int dir)
{
	void	*data;

	data = mlx_xpm_file_to_image(map->mlx_ptr, map->paths[dir],
			&map->textures[dir].width, &map->textures[dir].height);
	return (data);
}

int	direction(t_map *map, double ray_angle)
{
	int	dir;

	dir = 0;
	if (!map->intersect->was_hit_vertic)
	{
		if (is_ray_facing_up_dir(ray_angle))
			dir = NORTH;
		else if (is_ray_facing_down_dir(ray_angle))
			dir = SOUTH;
	}
	else
	{
		if (is_ray_facing_right_dir(ray_angle))
			dir = EAST;
		else if (is_ray_facing_left_dir(ray_angle))
			dir = WEST;
	}
	return (dir);
}

void	draw_ceiling_and_floor(t_map *map)
{
	int	j;
	int	color;
	int	i;

	j = -1;
	i = -1;
	while (++j < map->height)
	{
		i = -1;
		if (j < map->height / 2)
			color = map->ceil_color;
		else
			color = map->floor_color;
		while (++i < map->width)
			my_mlx_pixel_put(map->image, i, j, color);
	}
}

void	draw_line_rays(t_map *map, int x1, int y1, double ray_angle)
{
	map->bresenham->point1.x = x1;
	map->bresenham->point1.y = y1;
	map->bresenham->point2.x = x1 + (30 * cos(ray_angle));
	map->bresenham->point2.y = y1 + (30 * sin(ray_angle));
	draw_bresenhams_line(map);
}
