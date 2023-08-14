/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:16:42 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/08/14 14:54:30 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// # define FOV_ANGLE = 60 * (PIE / 180)
// # define WALL_STRIP_WIDTH = 1;

void draw_line_rays(t_map *map, int x1, int y1, double rayAngle)
{
	map->bresenham->point1.x = x1;
	map->bresenham->point1.y = y1;
	map->bresenham->point2.x = x1 + (30 * cos(rayAngle));
	map->bresenham->point2.y = y1 + (30 * sin(rayAngle));
	draw_bresenhams_line(map);
}

//write a function that will draw a rectangle like rect func in js:
void rect(t_map *map, int x, int y, double width, double height, int color)
{
	int j;
    (void)width;

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

	data = map->textures[dir].addr + ((int)of_y * map->textures[dir].line_length) + ((int)of_x * map->textures[dir].bits_per_pixel / 8);
	return (*(unsigned int *)data);
}
void render_wall(t_map *map, double wallStripHeight, bool is_vertic, int dir)
{
	int j;
	int	color;
	// char	*buff;
	double offset_x;
	double offset_y;
    j = -1;

	if (is_vertic)
		offset_x = fmodf(map->intersect->WallHitY , SCALE);
	else
		offset_x = fmodf(map->intersect->WallHitX , SCALE);
	offset_x = offset_x * map->textures[dir].width / SCALE;
    while (++j < (int)wallStripHeight)
    {
		offset_y = j * map->textures[dir].height / wallStripHeight;
		color = return_my_color(map, offset_x, offset_y, dir);
        if ((map->start->x > 0 && map->start->x < map->width)
            && (map->start->y + j > 0 && map->start->y + j < map->height))
            my_mlx_pixel_put(map->image, map->start->x, map->start->y + j, color);
    }
}

int	rgba_to_int(int r, int g, int b, double a)
{
	return ((int)(a * 255) << 24 | r << 16 | g << 8 | b);
}

void	*open_texture_files(t_map *map, int dir)
{
	void	*data;
	data = mlx_xpm_file_to_image(map->mlx_ptr, map->paths[dir], &map->textures[dir].width, &map->textures[dir].height);
	return (data);
}

int	direction(t_map *map, double rayAngle)
{
	int	dir;

	dir = 0;
	if (!map->intersect->wasHitVertic)
	{
		if (is_ray_facing_up_dir(rayAngle))
			dir = NORTH;
		else if (is_ray_facing_down_dir(rayAngle))
			dir = WEST;
	}
	else
	{
		if (is_ray_facing_right_dir(rayAngle))
			dir = EAST;
		else if (is_ray_facing_left_dir(rayAngle))
			dir = WEST;
	}
	// printf("dir====>: %d\n", dir);
	return (dir);
}

void	draw_ceiling_and_floor(t_map *map)
{
	int j;
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

void    draw_rays(t_map *map)
{
    double FOV_ANGLE = 60 * (PIE / 180);
    int num_rays = map->max_len * SCALE;
    double rayAngle = map->player->rotation_angel - (FOV_ANGLE / 2);
    int column_id = -1;
	t_directions	dir;

    double	wallStripHeight;
	double	distanceProjectionPlane;
	double	ray_distance;
	// double	color;
	// char	*data;

	dir = 0;
	draw_ceiling_and_floor(map);
	while (++column_id < num_rays)
	{
		dir = direction(map, rayAngle);
		cast_ray(map, rayAngle);
		ray_distance = map->intersect->distance * cos(rayAngle - map->player->rotation_angel);
		distanceProjectionPlane = (map->width / 2) / tan(FOV_ANGLE / 2);
		wallStripHeight = (SCALE / ray_distance) * distanceProjectionPlane;
		map->start->x = column_id;
		map->start->y = (map->height / 2) - (wallStripHeight / 2);
		map->end->x = column_id + 1;
		map->end->y = (int)map->start->y + (int)wallStripHeight;
		render_wall(map, wallStripHeight, map->intersect->wasHitVertic, dir);
		rayAngle += FOV_ANGLE / num_rays;
		rayAngle = normalize_angle(rayAngle);
	}
}
 