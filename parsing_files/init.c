/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:00:14 by arabiai           #+#    #+#             */
/*   Updated: 2023/07/14 11:02:51 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int count_map_lines(char **argv)
{
	int count;
	int map_fd;
	char *line;

	count = 0;
	map_fd = open(argv[1], O_RDONLY);
	line = get_next_line(map_fd);
	while (line /*&& count < 6*/)
	{
		if (line[0] == '1' || line[0] == '0' || line[0] == ' ')
			break;
		free(line);
		line = get_next_line(map_fd);
		count++;
	}
	count = 0;
	while (line)
	{
		free(line);
		line = get_next_line(map_fd);
		count++;
	}
	close(map_fd);
	return (count);
}

int count_text_lines(char **argv)
{
	int count;
	int map_fd;
	char *line;

	count = 0;
	map_fd = open(argv[1], O_RDONLY);
	line = get_next_line(map_fd);
	while (line)
	{
		if (line[0] == '1' || line[0] == '0' || line[0] == ' ')
		{
			free(line);
			break;
		}
		free(line);
		line = get_next_line(map_fd);
		count++;
	}
	close(map_fd);
	return (count);
}

void free_map(t_map *map)
{
	int i;

	i = -1;
	while (++i < 4)
		free(map->paths[i]);
	free(map->paths);
	i = -1;
	while (++i < map->rows)
		free(map->map[i]);
	free(map->map);
}

void initialize_map(t_map *map, char **argv)
{
	map->ceil_color = 0;
	map->floor_color = 0;
	map->rows = count_map_lines(argv);
	map->text_rows = count_text_lines(argv);
	map->map = NULL;
	map->paths = NULL;
}
