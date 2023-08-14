/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:29:48 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/08/14 19:51:46 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_square(t_map *map ,int x, int y, int color)
{
	int i;
	int j;

	i = SCALE/4 * x;
	j = SCALE/4 * y;
	while(i < SCALE/4 + (SCALE/4 * x))
	{
		j = SCALE/4 * y;
		while (j < SCALE/4 + (SCALE/4 * y))
		{
			if ((i > 0 && i < map->mini_width) && (j > 0 && j < map->mini_height))
			{
				if ((i == SCALE/4 * x || j == SCALE/4 * y) && color == 0xFFFFFF)
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

void draw_circle(t_map *map, double centerX, double centerY, int radius, int color)
{
    int x = 0;
    int y = radius;
    int decision = 3 - 2 * radius;
	
	int i;
    while (x <= y)
    {
		i = centerX - y;
        while (i <= centerX + y)
        {
			if ((i > 0 && i < map->mini_width) && (centerY + x > 0 && centerY + x < map->mini_height))
                my_mlx_pixel_put(map->mini_image, i, (int)centerY + x, color);
			if ((i > 0 && i < map->mini_width) && (centerY - x > 0 && centerY - x < map->mini_height))
                my_mlx_pixel_put(map->mini_image, i, (int)centerY - x, color);
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

double	normalize_angle(double angle)
{
	angle = fmod(angle, PIE * 2);
	if (angle < 0)
		angle = PIE * 2 + angle;
	return (angle);
}

// void get_color_and_draw_sqaure(t_map *map, int i, int j)
// {
// 	int		dir;
// 	int		color;

// 	dir = is_player(map->map[j][i]);
// 	if (map->map[j][i] == '1')
// 		color = 0x222222; // grey represents the walls
// 	else if (map->map[j][i] == '0')
// 		color = 0xFFFFFF; // white represents the the free space / floor
// 	else if (dir != -1)
// 		color = 0x228811; // green represents the player
// 	else
// 		color = 0x000000; // black represents the void
// 	draw_square(map, i, j, color);
// }



void	minimap(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	double mini_x = map->mini_width / 2;
	double mini_y = map->mini_height / 2;
	double new_x = map->player->x - mini_x;
	double new_y = map->player->y - mini_y;
	double tmp_y;
	double tmp_x;
	

	tmp_x = new_x;
	while (i < map->mini_width)
	{
		j = 0;
		tmp_y = new_y;
		while (j < map->mini_height)
		{
			if (is_there_a_wall(map, tmp_x, tmp_y) == -1)
				my_mlx_pixel_put(map->mini_image, i, j, 0x222222);
			else if (is_there_a_wall(map, tmp_x, tmp_y) == 1)
				my_mlx_pixel_put(map->mini_image, i, j, 0x222222);
			else
				my_mlx_pixel_put(map->mini_image, i, j, 0xa9a9a9);
			j++;
			tmp_y++;
		}
		i++;
		tmp_x++;
	}
	draw_circle(map, mini_x, mini_y, 4, 0xFF0000);
	draw_line(map, mini_x, mini_y); 
}
