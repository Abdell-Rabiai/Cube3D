/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 13:16:46 by arabiai           #+#    #+#             */
/*   Updated: 2023/09/04 11:48:23 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	make_map_rectangular_to_maxlen(t_map *map)
{
	int		i;
	int		len;
	char	*old_line;

	i = 0;
	while (map->map[i])
	{
		len = ft_strlen(map->map[i]);
		old_line = ft_strdup(map->map[i], 1);
		map->map[i] = malloc(sizeof(char) * (map->max_len + 1));
		ft_strlcpy(map->map[i], old_line, len + 1);
		while (len < map->max_len)
		{
			map->map[i][len] = ' ';
			len++;
		}
		map->map[i][len] = '\0';
		i++;
		free(old_line);
	}
}

int	parsing(char **argv, int argc, t_map *map)
{
	if (check_file_errors(argv, argc))
		exit (1);
	read_textures_colors(map, argv);
	if (check_text(map))
		exit (1);
	read_map(map, argv);
	make_map_rectangular_to_maxlen(map);
	if (check_map(map))
		exit (1);
	store_paths_colors(map);
	return (0);
}

void	get_starting_position(t_map *map)
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
					map->player->x = i * map->cube_size + map->cube_size / 2;
				if (map->player->y == -1)
					map->player->y = j * map->cube_size + map->cube_size / 2;
				if (map->player->dir == -1)
					map->player->dir = dir;
			}
			j++;
		}
		i++;
	}
}

void	get_player_position(t_map *map)
{
	get_starting_position(map);
	if (map->player->dir == NORTH)
		map->player->rotation_angel = -M_PI / 2;
	else if (map->player->dir == SOUTH)
		map->player->rotation_angel = M_PI / 2;
	else if (map->player->dir == EAST)
		map->player->rotation_angel = 0;
	else if (map->player->dir == WEST)
		map->player->rotation_angel = M_PI;
}

void	open_textures(t_map *map)
{
	int	dir;

	dir = -1;
	while (++dir < 4)
	{
		map->textures[dir].addr = mlx_get_data_addr(
				open_texture_files(map, dir),
				&map->textures[dir].bits_per_pixel,
				&map->textures[dir].line_length, &map->textures[dir].endian);
		if (map->textures[dir].addr == NULL)
		{
			printf("Error\nTexture file corrupted/invalid\n");
			exit(0);
		}
	}
}
