/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:11:30 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/07/20 08:18:03 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initialize_bresenhams_variables(t_bresenham *map)
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


void	draw_bresenhams_line(t_map *carte)
{
	t_bresenham *map;
	t_image *image;

	map = carte->bresenham;
	image = carte->image;
	initialize_bresenhams_variables(map);
	printf("map->point1.x = {%d}\n", map->point1.x);
	printf("map->point1.y = {%d}\n", map->point1.y);
	printf("map->point2.x = {%d}\n", map->point2.x);
	printf("map->point2.y = {%d}\n", map->point2.y);
	while (1)
	{
		if ((map->point1.x > 0 && map->point1.x < carte->width * SCALE)
			&& (map->point1.y > 0 && map->point1.y < carte->height * SCALE))
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

int	exit_hook(void)
{
	exit(0);
}

void update(t_map *map)
{
	t_player *player;

	player = map->player;
	player->rot_angel += player->turn_dir * player->rotation_speed;
	
	player->x += player->walk_dir * player->move_speed * cos(player->rot_angel);
	player->y += player->walk_dir * player->move_speed * sin(player->rot_angel);
}

int	key_hook(int keycode, t_map *map)
{
	t_image *image;
	
	image = map->image;
	printf("keycode = %d\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_window(map->image->mlx_ptr, map->image->window_ptr);
		map->image->window_ptr = NULL;
		exit(0);
	}
	else if (keycode == 126) // up forward
	{
		map->player->walk_dir = 1;
	}
	else if (keycode == 125)
	{
		map->player->walk_dir = -1; // down backword
	}
	else if (keycode == 124) // right turnright
	{
		map->player->turn_dir = 1;
	}
	else if (keycode == 123) // left turnleft
	{
		map->player->turn_dir = -1;
	}
	mlx_destroy_image(image->mlx_ptr, image->img);
	mlx_clear_window(image->mlx_ptr, image->window_ptr);
	image->img = mlx_new_image(image->mlx_ptr, map->height, map->width);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel, &image->line_length, &image->endian);
	update(map);
	minimap(map);
	mlx_put_image_to_window(image->mlx_ptr, image->window_ptr, image->img, 0, 0);
	return (0);
}

void initialize_map(t_map *map, char **argv)
{
	
	map->bresenham = malloc(sizeof(t_bresenham));
	map->image = malloc(sizeof(t_image));
	map->player = malloc(sizeof(t_player));

	map->player->x = 0;
	map->player->y = 0;
	map->player->dir = -1;
	map->player->turn_dir = 0; // 1 for right or -1 for left
	map->player->walk_dir = 0; // 1 for forward or -1 for backward
	map->player->rot_angel = PIE / 2;
	map->player->move_speed = 0.5; // PIXELS PER FRAME
	map->player->rotation_speed = 0.5; // ANGELS PER FRAME

	map->ceil_color = 0;
	map->floor_color = 0;
	map->rows = count_map_lines(argv);
	map->cols = count_map_cols(argv);
	map->text_rows = count_text_lines(argv);
	map->map = NULL;
	map->paths = NULL;
	map->width = map->cols * SCALE;
	map->height = map->rows * SCALE;

	map->image->mlx_ptr = mlx_init();
	map->image->window_ptr = mlx_new_window(map->image->mlx_ptr, map->height, map->width, "CUBE3D");
	map->image->img = mlx_new_image(map->image->mlx_ptr, map->height, map->width);
	map->image->addr = mlx_get_data_addr(map->image->img, &map->image->bits_per_pixel, &map->image->line_length, &map->image->endian);

}

int parsing(char **argv, int argc, t_map *map)
{
	if (check_file_errors(argv, argc))
		return (1);
	read_textures_colors(map, argv);
	read_map(map, argv);
	if (check_map(map) || check_text(map))
		return (1);
	store_paths_colors(map);
	print_map(map);
	return (0);
}

int main(int argc, char **argv)
{
	t_map *map;
	
	map = malloc(sizeof(t_map));
	initialize_map(map, argv);
	if (parsing(argv, argc, map))
		return (1);
	minimap(map);
	//play_game(&map, &info);
	mlx_put_image_to_window(map->image->mlx_ptr, map->image->window_ptr, map->image->img, 0, 0);
	mlx_hook(map->image->window_ptr, 2, (1L<<0), key_hook, map);
	mlx_hook(map->image->window_ptr, 17, 0, exit_hook, 0);
	mlx_loop(map->image->mlx_ptr);
	free_map(map);
}
