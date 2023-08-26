/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_map_text.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:07:27 by arabiai           #+#    #+#             */
/*   Updated: 2023/08/26 15:25:27 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	which_dir(char *dir)
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

void	read_textures_colors(t_map *map, char **argv)
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

void	get_dir(t_map *map, char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != 'N' && line[i] != 'S'
		&& line[i] != 'W' && line[i] != 'E')
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

void	read_the_map(int map_fd, char *line, t_map *map)
{
	int	i;

	i = 0;
	while (line)
	{
		map->map[i] = ft_strdup(ft_strtrim(line, "\n"), 1);
		get_dir(map, line);
		free(line);
		line = get_next_line(map_fd);
		i++;
	}
	map->map[i] = NULL;
}
