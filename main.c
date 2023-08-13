/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:11:30 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/08/13 17:20:42 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int key_rel(int key, t_map *map)
{
	if (key == 126)
		map->player->walk_dir = 0;
	if (key == 125)
		map->player->walk_dir = 0;
	if (key == 124)
		map->player->turn_dir = 0;
	if (key == 123)
		map->player->turn_dir = 0;
	return (0);
}

 void all_hooks(t_map *map)
 {
	mlx_hook(map->window_ptr, 2, (1L<<0), key_hook, map);
	mlx_hook(map->window_ptr, 6, (1L<< 0), key_rel, map);
	mlx_hook(map->window_ptr, ON_MOUSEMOVE, 0, mouse_hook, map);
	mlx_hook(map->window_ptr, 17, 0, exit_hook, map);
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
		map->player->rotation_angel = - M_PI / 2;
	else if (map->player->dir == SOUTH)
		map->player->rotation_angel = M_PI / 2;
	else if (map->player->dir == EAST)
		map->player->rotation_angel = 0;
	else if (map->player->dir == WEST)
		map->player->rotation_angel = M_PI;
}
void d(void)
{
	system("leaks cub3d");
}

void	open_textures(t_map *map)
{
	int	dir;

	dir = -1;
	while (++dir < 4)
		map->textures[dir].addr = mlx_get_data_addr(open_texture_files(map, dir), &map->textures[dir].bits_per_pixel
		, &map->textures[dir].line_length, &map->textures[dir].endian);
}

int main(int argc, char **argv)
{
	t_map *map;
	// atexit(d);
	map = malloc(sizeof(t_map));
	initialize_map(map, argv);
	if (parsing(argv, argc, map))
		return (1);
	get_player_position(map); // this function gets the player's position and direction
	draw_the_map(map);
	open_textures(map);
	draw_rays(map);
	mlx_put_image_to_window(map->mlx_ptr, map->window_ptr, map->image->img, 0, 0);
	all_hooks(map); // this function calls all the hooks that i need to move the player and the line
	mlx_loop(map->mlx_ptr);
	free_map(map);
}
