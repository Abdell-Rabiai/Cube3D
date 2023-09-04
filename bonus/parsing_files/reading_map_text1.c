/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_map_text1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:08:37 by arabiai           #+#    #+#             */
/*   Updated: 2023/09/04 12:01:58 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	read_map(t_map *map, char **argv)
{
	char	*line;
	int		map_fd;

	map_fd = open(argv[1], O_RDONLY);
	map->map = malloc(sizeof(char *) * (map->rows + 1));
	line = get_next_line(map_fd);
	while (!ft_strcmp(line, "\n") || line[0] == 'C' || line[0] == 'F'
		|| line[0] == 'N' || line[0] == 'S' || line[0] == 'W'
		|| line[0] == 'E')
	{
		free(line);
		line = get_next_line(map_fd);
		if (!line)
		{
			printf("Error\n No map found\n");
			exit(1);
		}
	}
	read_the_map(map_fd, line, map);
	close(map_fd);
}

int	get_ceil_floor_cols(char *line)
{
	char	**cols;
	char	*tmp;
	int		rgb;

	tmp = ft_strtrim(line + 1, " \n");
	if (!tmp)
		return (-1);
	if (count_words(tmp, ' ') != 3 && count_words(tmp, ' ') != 1 && count_words(tmp, ' ') != 2)
		return (free(tmp), -1);
	if (count_charset(tmp, ',') != 2)
		return (free(tmp), -1);
	cols = ft_split(tmp, ',');
	if (!cols)
		return (free(tmp), -1);
	if (ft_atoi(cols[0]) > 255 || ft_atoi(cols[0]) < 0 || ft_atoi(cols[1]) > 255
		|| ft_atoi(cols[1]) < 0 || ft_atoi(cols[2]) > 255
		|| ft_atoi(cols[2]) < 0)
		return (free(tmp), free_all(cols), -1);
	if (count_words(tmp, ',') != 3)
		return (free(tmp), free_all(cols), -1);
	rgb = (ft_atoi(cols[0]) << 16) + (ft_atoi(cols[1]) << 8) + ft_atoi(cols[2]);
	free_all(cols);
	free(tmp);
	return (rgb);
}

void	store_paths_colors(t_map *map)
{
	char	**arr;
	char	*tmp;
	int		i;
	int		dir;

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
			map->paths[dir] = tmp;
		}
		else if (arr[i][0] == 'F')
			map->floor_color = get_ceil_floor_cols(arr[i]);
		else if (arr[i][0] == 'C')
			map->ceil_color = get_ceil_floor_cols(arr[i]);
		i++;
	}
	map->paths[4] = NULL;
}
