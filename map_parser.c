/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdell_rabiai <abdell_rabiai@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:15:44 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/07/10 18:29:47 by abdell_rabi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	get_ceil_floor_cols(char *line)
{
	char    **cols;
	int		rgb;

	cols = ft_split(line + 2, ',');
	rgb = (ft_atoi(cols[0]) << 16) + (ft_atoi(cols[1]) << 8) + ft_atoi(cols[2]);
	free_all(cols);
	return (rgb);
}

void print_map(t_map *map)
{
	int i;

	i = -1;
	printf("ceil => %d\n", map->ceil_color);
	printf("floor => %d\n", map->floor_color);
	printf("path 1 => %s\n", map->paths[0]);
	printf("path 2 => %s\n", map->paths[1]);
	printf("path 3 => %s\n", map->paths[2]);
	printf("path 4 => %s\n", map->paths[3]);
	while (map->map[++i])
		printf("%s", map->map[i]);
}

int pars_map(int map_fd, t_map *map)
{
	char    *line;
	int     dir;
	int		i;

	i = 0;
	map->map = malloc(sizeof(char *) * (map->rows + 1));
	map->paths = malloc(sizeof(char *) * 4);
	line = get_next_line(map_fd);
	while (line)
	{
		dir = which_dir(line);
		if (dir != -1)
			map->paths[dir] = ft_strtrim(line + 2, " ");
		else if (!ft_strncmp(line, "F", 1))
			map->floor_color = get_ceil_floor_cols(line);
		else if (!ft_strncmp(line, "C", 1))
			map->ceil_color = get_ceil_floor_cols(line);
		else
			map->map[i++] = ft_strdup(line, 0);
		free(line);
		line = get_next_line(map_fd);
	}
	map->map[i] = NULL;
	print_map(map);
	return (0);
}

// what is a valid map ?
// 1. map must be surrounded by walls
// 2. map must have only 4 directions (N, S, E, W)


int	count_map_lines(int	fd)
{
	int		count;
	char	*line;

	count = 0;
	line = get_next_line(fd);
	while (line && count < 6)
	{
		free(line);
		line = get_next_line(fd);
		count++;
	}
	count = 0;
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		count++;
	}
	close(fd);
	return (count);
}

int	is_surrounded_by_walls(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->columns)
		{
			if ((i == 0 || i == map->rows - 1) && map->map[i][j] != '1')
					return (0);
			else if ((j == 0 || j == map->columns - 1) && map->map[i][j] != '1')
				return (0);
		}
	}
	return (1);
}