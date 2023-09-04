/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 06:06:13 by arabiai           #+#    #+#             */
/*   Updated: 2023/09/04 11:49:02 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_wall_collision(t_map *map, double x, double y)
{
	int	x0;
	int	y0;

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

int	is_wall(t_map *map, double x, double y)
{
	if (check_wall_collision(map, x, y) == 1)
		return (1);
	else if (check_wall_collision(map, x, y) == -1)
		return (-1);
	else
		return (0);
}

int	is_there_a_wall(t_map *map, double x, double y)
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

void	apply_the_changes(t_map *map)
{
	t_player	*player; 
	double		new_player_x;
	double		new_player_y;
	double		transaltion_distance;

	player = map->player;
	transaltion_distance = player->walk_dir * player->move_speed;
	player->rotation_angel += player->turn_dir * player->rotation_speed;
	player->rotation_angel = normalize_angle(player->rotation_angel);
	new_player_x = player->x + transaltion_distance
		* cos(player->rotation_angel) + (map->player->translate_y
			* -sin(player->rotation_angel));
	new_player_y = player->y + transaltion_distance
		* sin(player->rotation_angel) + (map->player->translate_y
			* cos(player->rotation_angel));
	if (!is_there_a_wall(map, new_player_x, new_player_y))
	{
		player->x = new_player_x;
		player->y = new_player_y;
	}
}

void	change_coordinates(t_map *map, int x2, int y2)
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
