/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:29:48 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/07/19 06:09:10 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_init_i_j(int *i, int *j, int x, int y, int dir)
{
	if (dir == NORTH)
	{
		*i = SCALE + (SCALE * x);
		*j = SCALE / 2 + (SCALE * y);
	}
	else if (dir == SOUTH)
	{
		*i = SCALE / 2 + (SCALE * x);
		*j = SCALE / 2 + (SCALE * y);
	}
	else if (dir == EAST)
	{
		*i = SCALE / 2 + (SCALE * x);
		*j = SCALE + (SCALE * y);
	}
	else if (dir == WEST)
	{
		*i = SCALE / 2 + (SCALE * x);
		*j = SCALE / 2 + (SCALE * y);
	}
}

void	ft_limits_of_while(int *i, int *j, int *x, int *y, int dir)
{
	if (dir == NORTH || dir == SOUTH)
	{
		*x = *i + SCALE / 2;
		*y = *j;
	}
	else if (dir == EAST || dir == WEST)
	{
		*x = *i;
		*y = *j + SCALE / 2;
	}
}

void	draw_direction_line(t_mlx_info *mlx_info, int x, int y, int dir)
{
	int i;
	int j;

	ft_init_i_j(&i, &j, x, y, dir);
	ft_limits_of_while(&i, &j, &x, &y, dir);
	while(++i < x)
	{
		while (++j < y)
		{
			if (dir == NORTH || dir == SOUTH)
				j = SCALE / 2 + (SCALE * y);
			else if (dir == EAST || dir == WEST)
				i = SCALE / 2 + (SCALE * x);
			mlx_pixel_put(mlx_info->mlx_ptr, mlx_info->window_ptr, i, j, 0x008800);
		}
	}
}

void	draw_square(t_mlx_info *info ,int x, int y, int color, int dir)
{
	int i;
	int j;

	i = SCALE * x - 1;
	j = SCALE * y;
	while(++i < SCALE + (SCALE * x))
	{
		j = SCALE * y - 1;
		while (++j < SCALE + (SCALE * y))
		{
			if ((i > 0 && i < WIDTH) && (j > 0 && j < HEIGHT))
				my_mlx_pixel_put(&info->image, i, j, color);
		}
	}
	if (dir != -1)
		draw_direction_line(info, x, y, dir);
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

void	minimap(t_map *map, t_mlx_info *mlx_info)
{
	int		i;
	int		j;
	int		row_len;
	int		dir;
	int		color;

	i = 0;
	while (i < map->rows - 1)
	{
		j = 0;
		row_len = ft_strlen(map->map[i]);
		while (j < row_len)
		{
			dir = is_player(map->map[i][j]);
			if (map->map[i][j] == '1')
				color = 0xFFFFFF;
			else if (map->map[i][j] == '0')
				color = 0x000000;
			else if (dir != -1)
				color = 0xFF0000;
			else
				color = 0x0000FF;
			draw_square(mlx_info, i, j, color, dir);
			j++;
		}
		i++;
	}
}
