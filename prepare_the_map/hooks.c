/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 06:06:13 by arabiai           #+#    #+#             */
/*   Updated: 2023/08/26 16:47:44 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	exit_hook(t_map *map)
{
	mlx_destroy_window(map->mlx_ptr, map->window_ptr);
	free_map(map);
	exit(0);
}

int check_wall_collision(t_map *map, double x, double y)
{
	int x0;
	int y0;
	if (x < 0 || x > map->width || y < 0 || y > map->height)
		return (-1);
	x0 = floor(x / map->cube_size);
	y0 = floor(y / map->cube_size);
	if (x0 < 0 || x0 > map->x - 1 || y0 < 0 || y0 > map->y - 1)
		return (-1);
	if (map->map[y0][x0] == '1' || map->map[y0][x0] == ' ')
		return (1);
	else
		return (0);
}
int is_wall(t_map *map, double x, double y)
{
	if (check_wall_collision(map, x, y) == 1)
		return (1);
	else if (check_wall_collision(map, x, y) == -1)
		return (-1);
	else
		return (0);
}
int is_there_a_wall(t_map *map, double x, double y)
{
	if (check_wall_collision(map, x, y - 3) == 1 || check_wall_collision(map, x, y - 3) == -1)
		return (1);
	else if (check_wall_collision(map, x + 3, y - 3) == 1 || check_wall_collision(map, x + 3, y - 3) == -1)
		return (1);
	else if (check_wall_collision(map, x + 3, y) == 1 || check_wall_collision(map, x + 3, y) == -1)
		return (1);
	else if (check_wall_collision(map, x + 3, y + 3) == 1 || check_wall_collision(map, x + 3, y + 3) == -1)
		return (1);
	else if (check_wall_collision(map, x, y + 3) == 1 || check_wall_collision(map, x, y + 3) == -1)
		return (1);
	else if (check_wall_collision(map, x - 3, y + 3) == 1 || check_wall_collision(map, x - 3, y + 3) == -1)
		return (1);
	else if (check_wall_collision(map, x - 3, y) == 1 || check_wall_collision(map, x - 3, y) == -1)
		return (1);
	else if (check_wall_collision(map, x - 3, y - 3) == 1 || check_wall_collision(map, x - 3, y - 3) == -1)
		return (1);
	return (0);
}


void apply_the_changes(t_map *map)
{
	t_player	*player; 
	double		new_player_x;
	double		new_player_y;
	double		transaltion_distance;

	player = map->player;
	transaltion_distance = player->walk_dir * player->move_speed;
	player->rotation_angel += player->turn_dir * player->rotation_speed;
	player->rotation_angel = normalize_angle(player->rotation_angel);
	new_player_x = player->x + transaltion_distance * cos(player->rotation_angel);
	new_player_y = player->y + transaltion_distance * sin(player->rotation_angel);
	if (!is_there_a_wall(map, new_player_x, new_player_y))
	{
		player->x = new_player_x;
		player->y = new_player_y;
	}
}

void change_coordinates(t_map *map, int x2, int y2)
{
	t_player	*player;
	int			x1;
	int			y1;

	player = map->player;
	x1 = player->x;
	y1 = player->y;
	if (x2 < 0 || x2 > map->width - 1 || y2 < 0 || y2 > map->height - 1)
		return ;
	if (x2 > player->previous_x)
		player->rotation_angel += player->rotation_speed;
	else
		player->rotation_angel -= player->rotation_speed;
	player->previous_x = x2;
	player->previous_y = y2;
}

void create_new_image(t_map *map, t_image *image)
{
    mlx_destroy_image(map->mlx_ptr, image->img);
	mlx_destroy_image(map->mlx_ptr, map->mini_image->img);
	mlx_clear_window(map->mlx_ptr, map->window_ptr);
	image->img = mlx_new_image(map->mlx_ptr, map->width, map->height);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel, &image->line_length, &image->endian);
	map->mini_image->img = mlx_new_image(map->mlx_ptr, map->mini_width, map->mini_height);
	map->mini_image->addr = mlx_get_data_addr(map->mini_image->img, &map->mini_image->bits_per_pixel, &map->mini_image->line_length, &map->mini_image->endian);
}

int	mouse_hook(int x, int y, t_map *map)
{
	t_image *image;
	
	image = map->image;
	create_new_image(map, image);
	change_coordinates(map, x, y);
	game(map);
	return (0);
}

int	key_released(int keycode, t_map *map)
{
	if (keycode == 13 || keycode == 126)
		map->player->walk_dir = 0;
	else if (keycode == 1 || keycode == 125)
		map->player->walk_dir = 0;
	else if (keycode == 2 || keycode == 124)
		map->player->turn_dir = 0;
	else if (keycode == 0 || keycode == 123)
		map->player->turn_dir = 0;
	return (0);
}

int	key_pressed(int keycode, t_map *map)
{
	if (keycode == 53)
	{
		mlx_destroy_window(map->mlx_ptr, map->window_ptr);
		free_map(map);
		exit(0);
	}
	if (keycode == 13 || keycode == 126)
		map->player->walk_dir = 1;
	else if (keycode == 1 || keycode == 125)
		map->player->walk_dir = -1;
	else if (keycode == 2 || keycode == 124)
		map->player->turn_dir = 1;
	else if (keycode == 0 || keycode == 123)
		map->player->turn_dir = -1;
	return (0);
}

int	draw_the_frame(t_map *map)
{
	t_image	*image;

	image = map->image;
	create_new_image(map, image);
	apply_the_changes(map);
	game(map);
	return (0);
}
