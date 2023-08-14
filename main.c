/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:11:30 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/08/14 15:56:59 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

 void all_hooks(t_map *map)
 {
	mlx_hook(map->window_ptr, 2, (1L<<0), key_hook, map);
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
	if (check_text(map))
		return (1);
	read_map(map, argv);
	if (check_map(map))
		return (1);
	make_map_rectangular_to_maxlen(map);
	store_paths_colors(map);
	return (0);
}

void get_starting_position(t_map *map)
{
	int		i;
	int		j;
	int		dir;

	i = 0;
	while (i < map->x)
	{
		j = 0;
		while (j < map->y)
		{
			dir = is_player(map->map[j][i]);
			if (dir != -1)
			{
				if (map->player->x == -1)
					map->player->x = i * SCALE + SCALE / 2;
				if (map->player->y == -1)
					map->player->y = j * SCALE + SCALE / 2;
				if (map->player->dir == -1)
					map->player->dir = dir;
			}
			j++;
		}
		i++;
	}
}

void get_player_position(t_map *map)
{	
	get_starting_position(map);
	if (map->player->dir == NORTH)
		map->player->rotation_angel = - PIE / 2;
	else if (map->player->dir == SOUTH)
		map->player->rotation_angel = PIE / 2;
	else if (map->player->dir == EAST)
		map->player->rotation_angel = 0;
	else if (map->player->dir == WEST)
		map->player->rotation_angel = PIE;
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

void draw_minimap(t_map *map)
{
	//modify player's position on the minimap
	minimap(map);
	draw_the_player(map);
}

void start_the_game(t_map *map)
{
	open_textures(map);
	draw_rays(map);
}

void game(t_map *map)
{
	start_the_game(map);
	draw_minimap(map);
	mlx_put_image_to_window(map->mlx_ptr, map->window_ptr, map->image->img, 0, 0);
	mlx_put_image_to_window(map->mlx_ptr, map->window_ptr, map->mini_image->img, 0, 0);
}

int main(int argc, char **argv)
{
	t_map *map;

	map = malloc(sizeof(t_map));
	initialize_map(map, argv);
	if (parsing(argv, argc, map))
		return (1);
	get_player_position(map);
	// print_map(map);
	game(map);
	all_hooks(map);
	mlx_loop(map->mlx_ptr);
	free_map(map);
}
