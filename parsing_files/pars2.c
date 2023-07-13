/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:15:44 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/07/13 18:51:36 by arabiai          ###   ########.fr       */
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

int	get_ceil_floor_cols(char *line)
{
	char    **cols;
	char	**tmp;
	int		rgb;
	
	tmp = ft_split(line, ' ');
	if (count_words(line, ' ') != 2)
		return (free_all(tmp), -1);
	cols = ft_split(tmp[1], ',');
	if (count_words(tmp[1], ',') != 3)
		return (free_all(tmp), free_all(cols), -1);
	rgb = (ft_atoi(cols[0]) << 16) + (ft_atoi(cols[1]) << 8) + ft_atoi(cols[2]);
	free_all(cols);
	free_all(tmp);
	return (rgb);
}

void print_map(t_map *map)
{
	int i;

	i = -1;
	printf("ceil => (%d)\n", map->ceil_color);
	printf("floor => (%d)\n", map->floor_color);
	printf("path 1 => (%s)\n", map->paths[0]);
	printf("path 2 => (%s)\n", map->paths[1]);
	printf("path 3 => (%s)\n", map->paths[2]);
	printf("path 4 => (%s)\n", map->paths[3]);
	while (map->map[++i])
		printf("(%s)", map->map[i]);
}

int first_string_len(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	return (i);
}

int read_data(char **argv, t_map *map)
{
	char	*line;
	char	*tmp;
	int     dir;
	int		i;
	int		map_fd;

	i = 0;
	map_fd = open(argv[1], O_RDONLY);
	map->map = malloc(sizeof(char *) * (map->rows + 1));
	map->paths = malloc(sizeof(char *) * 4);
	line = get_next_line(map_fd);
	while (line)
	{
		dir = which_dir(line);
		if (dir != -1)
		{
			tmp = ft_strtrim(line + 2, " ");
			map->paths[dir] = ft_substr(tmp, 0, first_string_len(tmp), 1);
		}
		else if (!ft_strncmp(line, "F", 1))
			map->floor_color = get_ceil_floor_cols(line);
		else if (!ft_strncmp(line, "C", 1))
			map->ceil_color = get_ceil_floor_cols(line);
		else if (ft_strcmp(line, "\n"))
			map->map[i++] = ft_strdup(line, 0);
		free(line);
		line = get_next_line(map_fd);
	}
	map->map[i] = NULL;
	close(map_fd);
	return (0);
}


int	count_map_lines(char **argv)
{
	int		count;
	int		map_fd;
	char	*line;

	count = 0;
	map_fd = open(argv[1], O_RDONLY);
	line = get_next_line(map_fd);
	while (line && count < 6)
	{
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
	int		count;
	int		map_fd;
	char	*line;

	count = 0;
	map_fd = open(argv[1], O_RDONLY);
	line = get_next_line(map_fd);
	while (line)
	{
		if (line[0] == '1' || line[0] == '0' || line[0] == ' ')
		{
			free(line);
			break ;
		}
		free(line);
		line = get_next_line(map_fd);
		count++;
	}
	close(map_fd);
	return (count);
}
