/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:11:30 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/07/13 19:45:39 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void initialize_map(t_map *map, char **argv)
{
	map->ceil_color = 0;
	map->floor_color = 0;
	map->rows = count_map_lines(argv);
	map->text_rows = count_text_lines(argv);
	map->map = NULL;
	map->paths = NULL;
}

void	free_map(t_map *map)
{
	int	i;

	i = -1;
	while (++i < 4)
		free(map->paths[i]);
	free(map->paths);
	i = -1;
	while (++i < map->rows)
		free(map->map[i]);
	free(map->map);
}

void read_textures_colors(t_map *map, char **argv)
{
	char	*line;
	int		map_fd;
	int		i;

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

void print_text(t_map *map)
{
	int i;

	i = 0;
	while (i < map->text_rows)
	{
		printf("[%s]\n", map->text[i]);
		i++;
	}
}

void print_map1(t_map *map)
{
	int i;

	i = 0;
	while (map->map[i])
	{
		printf("{%s}\n", map->map[i]);
		i++;
	}
}

void print_paths(t_map *map)
{
	int i;

	i = 0;
	while (i < 4)
	{
		printf("(%s)\n", map->paths[i]);
		i++;
	}
}

void read_map(t_map *map, char **argv)
{
	char	*line;
	int		map_fd;
	int		i;

	i = 0;
	map_fd = open(argv[1], O_RDONLY);
	map->map = malloc(sizeof(char *) * (map->rows + 1));
	line = get_next_line(map_fd);
	while (!ft_strcmp(line, "\n") || line[0] == 'C' || line[0] == 'F' || line[0] == 'N'
		|| line[0] == 'S' || line[0] == 'W' || line[0] == 'E')
	{
		free(line);
		line = get_next_line(map_fd);
	}
	while (line)
	{
		map->map[i] = ft_strdup(ft_strtrim(line, "\n"), 1);
		free(line);
		line = get_next_line(map_fd);
		i++;
	}
	map->map[i] = NULL;
	close(map_fd);
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
			map->paths[dir] = ft_substr(tmp, 0, first_string_len(tmp), 1);
		}
		else if (arr[i][0] == 'F')
			map->floor_color = get_ceil_floor_cols(arr[i]);
		else if (arr[i][0] == 'C')
			map->ceil_color = get_ceil_floor_cols(arr[i]);
		i++;
	}
	map->paths[4] = NULL;
}

int check_text(t_map *map)
{
	char **text;
	int i;
	char *sub;
	char *trim;

	sub = NULL;
	trim = NULL;
	text = map->text;
	i = 0;
	while (text[i])
	{
		if ((!ft_strncmp(text[i], "F", 1) || !ft_strncmp(text[i], "C", 1) ) && ft_strcmp(text[i], "\n"))
		{
			if (get_ceil_floor_cols(text[i]) == -1)
				return (printf("Error\nInvalid color\n"), 1);
		}
		else if (which_dir(text[i]) == -1 && ft_strcmp(text[i], "\n"))
			return (printf("Error\nInvalid texture path\n"), 1);
		else if (which_dir(text[i]) != -1 && ft_strcmp(text[i], "\n"))
		{
			trim = ft_strtrim(text[i] + 2, " .\n");
			sub = ft_substr(trim, 0, first_string_len(trim), 1);
			if (access(sub, F_OK) != 0)
			{
				printf("path = [%s]\n", sub);
				free(sub);
				return (printf("Error\nTexture path not accessible\n"), 1);
			}
			free(sub);
		}
		i++;
	}
	return 0;
}

int check_map(t_map *map)
{
	char **mp;
	int i;
	
	i = 0;
	mp = map->map;
	if (check_invalid_characters(mp))
		return (1);
	if (check_multiple_players(mp))
		return (printf("Error\nMultiple players\n"), 1);
	if (check_is_closed(mp))
		return (printf("Error\nMap is not closed\n"), 1);
	return 0;
}

int main(int argc, char **argv)
{
	t_map	map;

	initialize_map(&map, argv);
	if (check_file_errors(argv, argc))
		return (1);
	read_textures_colors(&map, argv);
	read_map(&map, argv);
	if (check_map(&map) || check_text(&map))
		return (1);
	// if everything is ok store map and text and print everything
	store_paths_colors(&map);
	print_map(&map);
	free_map(&map);
	while (1);
}
