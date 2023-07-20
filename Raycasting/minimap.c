/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:29:48 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/07/20 11:47:53 by arabiai          ###   ########.fr       */
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

void	draw_direction_line(t_image *image, int x, int y, int dir)
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
			mlx_pixel_put(image->mlx_ptr, image->window_ptr, i, j, 0x008800);
		}
	}
}

void	draw_square(t_map *map ,int x, int y, int color)
{
	int i;
	int j;

	i = SCALE * x;
	j = SCALE * y;
	while(i < SCALE + (SCALE * x))
	{
		j = SCALE * y;
		while (j < SCALE + (SCALE * y))
		{
			if ((i > 0 && i < map->height) && (j > 0 && j < map->width))
			{
				if ((i == SCALE * x || j == SCALE * y) && color == 0xFFFFFF)
					my_mlx_pixel_put(map->image, i, j, 0x222222);
				else
					my_mlx_pixel_put(map->image, i, j, color);
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

void draw_circle(t_map *map, int centerX, int centerY, int radius, int color)
{
    int x = 0;
    int y = radius;
    int decision = 3 - 2 * radius;
	
	int i;
    while (x <= y)
    {
        // Draw vertical lines to fill the disc
		i = centerX - y;
        while (i <= centerX + y)
        {
            if ((i >= 0 && i < map->height) && (centerY + x >= 0 && centerY + x < map->width))
                my_mlx_pixel_put(map->image, i, centerY + x, color);
            if ((i >= 0 && i < map->height) && (centerY - x >= 0 && centerY - x < map->width))
                my_mlx_pixel_put(map->image, i, centerY - x, color);
			i++;
        }
        if (decision < 0)
            decision += 4 * x + 6;
        else
        {
            decision += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void linee(t_map *map, int x1, int y1)
{
	map->bresenham->point1.x = x1;
	map->bresenham->point1.y = y1;
	map->bresenham->point2.x = x1 + (30 * cos(map->player->rot_angel));
	map->bresenham->point2.y = y1 + (30 * sin(map->player->rot_angel));
	draw_bresenhams_line(map);
}

void	minimap(t_map *map)
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
		while (j < row_len )
		{
			dir = is_player(map->map[i][j]);
			if (map->map[i][j] == '1')
				color = 0x222222; // grey represents the walls
			else if (map->map[i][j] == '0')
				color = 0xFFFFFF; // white represents the the free space / floor
			else if (dir != -1)
				color = 0x228811; // green represents the player
			else
				color = 0x000000; // black represents the void
			if (dir != -1)
			{
				// hanta a khy lmoudir hahowa l commentaire li tlbti
				if (map->player->x == 0)
					map->player->x = (SCALE * i + SCALE / 2);
				if (map->player->y == 0)
					map->player->y = (SCALE * j + SCALE / 2);
				if (map->player->dir == -1)
					map->player->dir = dir;
				draw_circle(map, map->player->x, map->player->y, 8, color);
			}
			else
				draw_square(map, i, j, color);
			j++;
		}
		i++;
	}
	linee(map, map->player->x, map->player->y);
}
