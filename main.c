/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:11:30 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/08/03 16:20:48 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

 void all_hooks(t_map *map)
 {
	mlx_hook(map->image->window_ptr, 2, (1L<<0), key_hook, map);
	mlx_hook(map->image->window_ptr, ON_MOUSEMOVE, 0, mouse_hook, map);
	mlx_hook(map->image->window_ptr, 17, 0, exit_hook, 0);
	mlx_loop(map->image->mlx_ptr);
 }

void make_map_rectangular_to_maxlen(t_map *map)
{
	int i;
	int len;
	char *old_line;

	i = 0;
	while (map->map[i])
	{
		len = ft_strlen(map->map[i]);
		old_line = ft_strdup(map->map[i], 1);
		map->map[i] = malloc(sizeof(char) * (map->max_len + 1));
		ft_strlcpy(map->map[i], old_line, len + 1);
		while (len < map->max_len)
		{
			map->map[i][len] = '1';
			len++;
		}
		map->map[i][len] = '\0';
		i++;
		free(old_line);
	}
}

int parsing(char **argv, int argc, t_map *map)
{
	if (check_file_errors(argv, argc))
		return (1);
	read_textures_colors(map, argv);
	read_map(map, argv);
	make_map_rectangular_to_maxlen(map);
	if (check_map(map) || check_text(map))
		return (1);
	store_paths_colors(map);
	return (0);
}

void get_player_position(t_map *map)
{
		
	if (map->player->dir == NORTH)
		map->player->rotation_angel = - PIE / 2;
	else if (map->player->dir == SOUTH)
		map->player->rotation_angel = PIE / 2;
	else if (map->player->dir == EAST)
		map->player->rotation_angel = 0;
	else if (map->player->dir == WEST)
		map->player->rotation_angel = PIE;
}

int main(int argc, char **argv)
{
	t_map *map;
	
	map = malloc(sizeof(t_map));
	initialize_map(map, argv);
	if (parsing(argv, argc, map))
		return (1);
	print_map(map);
	get_player_position(map); // this function gets the player's position and direction
	draw_the_map(map); // this function draws the map and the player
	mlx_put_image_to_window(map->image->mlx_ptr, map->image->window_ptr, map->image->img, 0, 0);
	all_hooks(map); // this function calls all the hooks that i need to move the player and the line
	// mlx_loop_hook(map->image->mlx_ptr, draw_the_map, map);
	mlx_loop(map->image->mlx_ptr);
	free_map(map);
}
