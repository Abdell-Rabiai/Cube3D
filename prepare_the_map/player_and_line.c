/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_and_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 06:02:45 by arabiai           #+#    #+#             */
/*   Updated: 2023/07/22 08:10:54 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void draw_line(t_map *map, int x1, int y1)
{
	// draw a line from point (x1, y1) which is the player's initial position to the point (x2, y2) which is the player's direction
	// in which x2 = x1 + 30 * cos(rotation_angel) and y2 = y1 + 30 * sin(rotation_angel)
	// the 30 is the length of the line and we multiply it by cos(rotation_angel) and sin(rotation_angel) to get the x2 and y2
	// because cos(rot_angel) = adjacent / hypotenuse = x2 - x1 / 30 ===> x2 = x1 + 30 * cos(rot_angel)
	// and sin(rot_angel) = opposite / hypotenuse = y2 - y1 / 30 ====> y2 = y1 + 30 * sin(rot_angel)
	map->bresenham->point1.x = x1;
	map->bresenham->point1.y = y1;
	map->bresenham->point2.x = x1 + (30 * cos(map->player->rotation_angel));
	map->bresenham->point2.y = y1 + (30 * sin(map->player->rotation_angel));
	// now we've got the two points we need to draw the line between them
	// so each time we call the draw_line function we vary the rotation_angel by 0.44 or -0.44 which is the rotation_speed
	// go to init_map.c to see how we vary the rotation_angel
	draw_bresenhams_line(map);
}

void draw_the_player(t_map *map) // this functino represents the player as a little green circle and a line that shows the direction of the player
{
	draw_circle(map, map->player->x, map->player->y, 4, 0x228811); // the little green solid circle
	draw_line(map, map->player->x, map->player->y); // the line that shows the direction of the player
}

int draw_the_map(t_map *map) // this function draws the map and the player
{
	minimap(map); // this function draws the map only
	draw_the_player(map); // and this one adds the player to the map
	return (0);
}

void	initialize_bresenhams_variables(t_bresenham *map) // this function initializes the variables needed for the bresenhams algorithm
{
	map->dx = abs(map->point2.x - map->point1.x);
	map->dy = -abs(map->point2.y - map->point1.y);
	if (map->point1.x < map->point2.x)
		map->step_x = 1;
	else
		map->step_x = -1;
	if (map->point1.y < map->point2.y)
		map->step_y = 1;
	else
		map->step_y = -1;
	map->err = map->dx + map->dy;
}

// this function draws the line between the two points using the bresenhams algorithm
//hadchi la biti tfhmo khassk demonstrer 3lih mathematiquemnt o katkhd dakchi katranslitih l algorithm
void	draw_bresenhams_line(t_map *carte) 
{
	t_bresenham *map;
	t_image *image;

	map = carte->bresenham;
	image = carte->image;
	initialize_bresenhams_variables(map);
	while (1)
	{
		if ((map->point1.x > 0 && map->point1.x < carte->width)
			&& (map->point1.y > 0 && map->point1.y < carte->height))
			my_mlx_pixel_put(image, map->point1.x, map->point1.y, 0x228811);
		if (map->point1.x == map->point2.x
			&& map->point1.y == map->point2.y)
			break ;
		map->e2 = 2 * map->err;
		if (map->e2 >= map->dy)
		{
			map->err = map->err + map->dy;
			map->point1.x = map->point1.x + map->step_x;
		}
		else if (map->e2 <= map->dx)
		{
			map->err = map->err + map->dx;
			map->point1.y = map->point1.y + map->step_y;
		}
	}
}
