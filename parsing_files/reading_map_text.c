/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_map_text.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:07:27 by arabiai           #+#    #+#             */
/*   Updated: 2023/07/22 14:02:24 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int which_dir(char *dir)
{
	if (!ft_strncmp(dir, "NO", 2))
		return (NORTH);
	else if (!ft_strncmp(dir, "SO", 2))
		return (SOUTH);
	else if (!ft_strncmp(dir, "EA", 2))
		return (EAST);
	else if (!ft_strncmp(dir, "WE", 2))
		return (WEST);
	else
		return (-1);
}

void read_textures_colors(t_map *map, char **argv)
{
	char *line;
	int map_fd;
	int i;

	i = 0;
	map_fd = open(argv[1], O_RDONLY);
	map->text = malloc(sizeof(char *) * (map->text_rows + 1));
	line = get_next_line(map_fd);
	while (line && i < map->text_rows)
	{
		map->text[i] = ft_strdup(line, 0);
		free(line);
		line = get_next_line(map_fd);
		i++;
	}
	free(line);
	map->text[i] = NULL;
	close(map_fd);
}

void get_dir(t_map *map, char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] != 'N' && line[i] != 'S' && line[i] != 'W' && line[i] != 'E')
		i++;
	if (line[i] == 'N')
		map->player->dir = NORTH;
	else if (line[i] == 'S')
		map->player->dir = SOUTH;
	else if (line[i] == 'W')
		map->player->dir = WEST;
	else if (line[i] == 'E')
		map->player->dir = EAST;
}

void read_map(t_map *map, char **argv)
{
	char *line;
	int map_fd;
	int i;

	i = 0;
	map_fd = open(argv[1], O_RDONLY);
	map->map = malloc(sizeof(char *) * (map->rows + 1));
	line = get_next_line(map_fd);
	while (!ft_strcmp(line, "\n") || line[0] == 'C' || line[0] == 'F' || line[0] == 'N' || line[0] == 'S' || line[0] == 'W' || line[0] == 'E')
	{
		free(line);
		line = get_next_line(map_fd);
	}
	while (line)
	{
		map->map[i] = ft_strdup(ft_strtrim(line, "\n"), 1);
		get_dir(map, line);
		free(line);
		line = get_next_line(map_fd);
		i++;
	}
	map->map[i] = NULL;
	close(map_fd);
}

int get_ceil_floor_cols(char *line)
{
	char **cols;
	char **tmp;
	int rgb;

	tmp = ft_split(line, ' ');
	if (!tmp)
		return (-1);
	if (count_words(line, ' ') != 2)
		return (free_all(tmp), -1);
	if (count_charset(tmp[1], ',') != 2)
		return (free_all(tmp), -1);
	cols = ft_split(tmp[1], ',');
	if (!cols)
		return (free_all(tmp), -1);
	if (count_words(tmp[1], ',') != 3)
		return (free_all(tmp), free_all(cols), -1);
	rgb = (ft_atoi(cols[0]) << 16) + (ft_atoi(cols[1]) << 8) + ft_atoi(cols[2]);
	free_all(cols);
	free_all(tmp);
	return (rgb);
}

void store_paths_colors(t_map *map)
{
	char **arr;
	char *tmp;
	int i;
	int dir;

	i = 0;
	dir = 0;
	arr = map->text;
	map->paths = malloc(sizeof(char *) * 5);
	while (arr[i])
	{
		dir = which_dir(arr[i]);
		if (dir != -1)
		{
			tmp = ft_strtrim(arr[i] + 2, " .\n");
			map->paths[dir] = ft_substr(tmp, 0, word_length(tmp, ' '), 1);
		}
		else if (arr[i][0] == 'F')
			map->floor_color = get_ceil_floor_cols(arr[i]);
		else if (arr[i][0] == 'C')
			map->ceil_color = get_ceil_floor_cols(arr[i]);
		i++;
	}
	map->paths[4] = NULL;
}
