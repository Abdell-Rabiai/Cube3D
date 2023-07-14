/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:16:49 by arabiai           #+#    #+#             */
/*   Updated: 2023/07/14 09:27:39 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int check_valid_map_line(char *line)
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
		if (check_valid_map_line(tmp))
			return (free(tmp), 1);
		free(tmp);
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
