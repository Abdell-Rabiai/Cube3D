/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:29:48 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/08/26 14:46:49 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_square(t_map *map ,int x, int y, int color)
{
	int		i;
	int		j;

	i = map->cube_size / 4 * x;
	j = map->cube_size / 4 * y;
	while (i < map->cube_size / 4 + (map->cube_size / 4 * x))
	{
		j = map->cube_size / 4 * y;
		while (j < map->cube_size / 4 + (map->cube_size / 4 * y))
		{
			if ((i > 0 && i < map->mini_width)
				&& (j > 0 && j < map->mini_height))
			{
				if ((i == map->cube_size / 4 * x || j == map->cube_size / 4 * y)
						&& color == 0xFFFFFF)
					my_mlx_pixel_put(map->mini_image, i, j, 0x222222);
				else
					my_mlx_pixel_put(map->mini_image, i, j, color);
			}
			j++;
		}
		i++;
	}
}

int	is_player(char dir)
{
	if (dir == 'N')
		return (NORTH);
	else if (dir == 'S')
		return (SOUTH);
	else if (dir == 'E')
		return (EAST);
	else if (dir == 'W')
		return (WEST);
	return (-1);
}

void	draw_circle(t_map *map)
{
	int		i;
	int		j;
	double	angle;
	double	radius;

	i = 0;
	radius = 4;
	while (i < 360)
	{
		angle = i * M_PI / 180;
		j = 0;
		while (j < radius)
		{
			my_mlx_pixel_put(map->mini_image, map->mini_x + cos(angle) * j,
				map->mini_y + sin(angle) * j, 0xFF0000);
			j++;
		}
		i++;
	}
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, M_PI * 2);
	if (angle < 0)
		angle = M_PI * 2 + angle;
	return (angle);
}

void	minimap(t_map *map)
{
	int		i;
	int		j;
	double	tmp_y;
	double	tmp_x;

	i = 0;
	tmp_x = map->new_x;
	while (i < map->mini_width)
	{
		j = 0;
		tmp_y = map->new_y;
		while (j < map->mini_height)
		{
			if (is_wall(map, tmp_x, tmp_y) == -1)
				my_mlx_pixel_put(map->mini_image, i, j, 0x222222);
			else if (is_wall(map, tmp_x, tmp_y) == 1)
				my_mlx_pixel_put(map->mini_image, i, j, 0xC2F5C9);
			else
				my_mlx_pixel_put(map->mini_image, i, j, 0xa9a9a9);
			j++;
			tmp_y++;
		}
		i++;
		tmp_x++;
	}
}
