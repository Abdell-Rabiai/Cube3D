/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:49:07 by arabiai           #+#    #+#             */
/*   Updated: 2023/07/14 08:52:51 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int is_valid_map_line(char *line)
{
	int i;

	i = 0;
	if (!ft_strcmp(line, ""))
		return (printf("Error\nEmpty line in the map\n"), 1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '0' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W' && line[i] != '\n')
			{
				printf("character[%d] = [%c]\n", i, line[i]);
				return (printf("Error\nInvalid characters in map\n"), 1);
			}
		i++;
	}
	return (0);
}
int check_invalid_characters(char **arr)
{
	int	i;
	char *tmp;
	
	i = 0;
	while (arr[i])
	{
		tmp = ft_strtrim(arr[i], " ");
		if (is_valid_map_line(tmp))
			return (free(tmp), 1);
		free(tmp);
		i++;
	}
	return (0);
}

int check_file_errors(char **argv, int argc)
{
	int fd;

	if (argc != 2)
		return (printf("Error\nWrong number of arguments\n"), 1);
	else if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
		return (printf("Error\nFile format not correct\n"), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (printf("Error\nFile not found\n"), 1);
	close(fd);
	return (0);
}

int check_right(char **arr, int i, int j)
{
	while (arr[i][j] != '\0' && arr[i][j] == '0')
		j++;
	if (arr[i][j] != '1' && arr[i][j] != 'N' && arr[i][j] != 'S' && arr[i][j] != 'E' && arr[i][j] != 'W')
	{
		printf("right ==> [%c]\n", arr[i][j]);
		return (1);
	}
	return (0);
}
int check_left(char **arr, int i, int j)
{
	while (j > 0 && arr[i][j] == '0')
		j--;
	if (arr[i][j] != '1' && arr[i][j] != 'N' && arr[i][j] != 'S' && arr[i][j] != 'E' && arr[i][j] != 'W')
	{
		printf("left ==> [%c]\n", arr[i][j]);
		return (1);
	}
	return (0);
}
int check_up(char **arr, int i, int j)
{
	while (i > 0 && arr[i][j] == '0')
		i--;
	if (ft_strlen(arr[i]) - 1 < (size_t)j)
		return (1);
	if (arr[i][j] != '1' && arr[i][j] != 'N' && arr[i][j] != 'S' && arr[i][j] != 'E' && arr[i][j] != 'W')
	{
		printf("up ==> [%c]\n", arr[i][j]);
		return (1);
	}
	return (0);
}
int check_down(char **arr, int i, int j)
{
	while (arr[i][j] != '\0' && arr[i][j] == '0')
		i++;
	if (ft_strlen(arr[i]) - 1 < (size_t)j)
		return (1);
	if (arr[i][j] != '1' && arr[i][j] != 'N' && arr[i][j] != 'S' && arr[i][j] != 'E' && arr[i][j] != 'W')
	{
		printf("down ==> [%c]\n", arr[i][j]);
		return (1);
	}
	return (0);
}

int check_is_closed(char **arr)
{
	int i;
	int j;

	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j] != '\0')
		{
			if (arr[i][j] == '0')
			{
				if (check_right(arr, i, j) || check_left(arr, i, j)
					|| check_up(arr, i, j) || check_down(arr, i, j))
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int check_multiple_players(char **arr)
{
	int i;
	int j;
	int count;

	i = 0;
	count = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j] != '\0')
		{
			if (arr[i][j] == 'N' || arr[i][j] == 'S' || arr[i][j] == 'E' || arr[i][j] == 'W')
				count++;
			j++;
		}
		i++;
	}
	if (count > 1)
		return (1);
	return (0);
}