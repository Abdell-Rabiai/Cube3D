/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:11:30 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/07/13 11:48:04 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void initialize_map(t_map *map, char **argv)
{
	map->ceil_color = 0;
	map->floor_color = 0;
	map->rows = count_map_lines(argv);
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

int is_valid_map_line(char *line)
{
	int i;

	i = 0;
	if (!ft_strcmp(line, "\n"))
		return (1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '0' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W' && line[i] != '\n')
			{
				printf("line[%d] = %c\n", i, line[i]);
				return (1);
			}
		i++;
	}
	return (0);
}
int check_invalid_characters(int fd)
{
	int	i;
	char *line;
	char *tmp;
	
	i = 0;
	while (i++ < 6)
	{
		line = get_next_line(fd);
		free(line);
	}
	line = get_next_line(fd);
	while (!ft_strcmp(line, "\n"))
	{
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	line = get_next_line(fd);
	while (line)
	{
		tmp = ft_strtrim(line, " ");
		if (is_valid_map_line(tmp))
			return (1);
		free(tmp);
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int pars_for_errors(char **argv, int argc)
{
	int fd;

	if (argc != 2)
		return (printf("Error\nWrong number of arguments\n"), 1);
	else if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
		return (printf("Error\nFile format not correct\n"), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (printf("Error\nFile not found\n"), 1);
	if (check_invalid_characters(fd))
		return (printf("Error\nInvalid characters in map\n"), 1);
	return (0);
}

int check_right(char **arr, int i, int j)
{
	printf("the coordinates of the first 0 : (%d, %d)\n", i, j);
	while (arr[i][j] != '\0' && arr[i][j] == '0')
		j++;
	printf("to the right ==> [%c]\n", arr[i][j]);
	if (arr[i][j] != '1')
		return (1);
	return (0);
}
int check_left(char **arr, int i, int j)
{
	while (j > 0 && arr[i][j] == '0')
		j--;
	printf("to the left ==> [%c]\n", arr[i][j]);
	if (arr[i][j] != '1')
		return (1);
	return (0);
}
int check_top(char **arr, int i, int j)
{
	(void)arr;
	(void)i;
	(void)j;
	// printf("i = %d, j = %d\n", i, j);
	return (0);
}
int check_down(char **arr, int i, int j)
{
	(void)arr;
	(void)i;
	(void)j;
	// printf("i = %d, j = %d\n", i, j);
	return (0);
}

int check_is_closed(t_map *map)
{
	char **arr;
	int i;
	int j;

	i = 0;
	arr = map->map;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j] != '\0' && arr[i][j] != '0')
			j++;
		if (arr[i][j] == '\0')
			j = 0;
		else
		{
			if (check_right(arr, i, j) || check_left(arr, i, j)
				|| check_top(arr, i, j) || check_down(arr, i, j))
				return (1);
		}
		i++;
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_map	map;

	if (pars_for_errors(argv, argc))
		return (1);
	initialize_map(&map, argv);
	if (read_data(argv, &map))
		return (1);	
	if (check_is_closed(&map))
		return (printf("Error\nMap is not closed\n"), 1);
	free_map(&map);
	while (1);
}


// while (arr[i][++j])
// {
// 	if (arr[i][j] == '0' || arr[i][j] == '2')
// 	{
// 		if (i == 0 || i == map->rows - 1 || j == 0 || j == (int)ft_strlen(arr[i]) - 1)
// 			return (1);
// 		if (arr[i][j - 1] == ' ' || arr[i][j + 1] == ' ' || arr[i - 1][j] == ' ' || arr[i + 1][j] == ' ')
// 			return (1);
// 	}
// }	*/