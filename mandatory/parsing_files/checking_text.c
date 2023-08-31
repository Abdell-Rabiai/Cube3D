/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_text.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:20:11 by arabiai           #+#    #+#             */
/*   Updated: 2023/08/31 12:06:38 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_path_access(char *str)
{
	char	*trim;

	trim = ft_strtrim(str + 2, " .\n");
	if (open(trim, O_RDONLY) == -1)
	{
		printf("Error\n");
		printf("Texture path not accessible\n");
		printf("path => %s\n", trim);
		free(trim);
		return (1);
	}
	free(trim);
	return (0);
}

int	func(int count)
{
	if (count < 6)
		return (printf("Error\nMissing texture or color\n"), 1);
	else if (count > 6)
		return (printf("Error\nToo many texture or color\n"), 1);
	return (0);
}

bool	condum(t_map *map, int i)
{
	if ((!ft_strncmp(map->text[i], "F", 1) || !ft_strncmp(map->text[i], "C", 1))
		&& ft_strcmp(map->text[i], "\n"))
		return (true);
	return (false);
}

int	check_text(t_map *map)
{
	int	count;
	int	i;

	i = -1;
	count = 0;
	while (map->text[++i])
	{
		if (condum(map, i))
		{
			count++;
			if (get_ceil_floor_cols(map->text[i]) == -1)
				return (printf("Error\nInvalid color\n"), 1);
		}
		else if (which_dir(map->text[i]) == -1 && ft_strcmp(map->text[i], "\n"))
			return (printf("Error\nInvalid texture path\n"), 1);
		else if (which_dir(map->text[i]) != -1 && ft_strcmp(map->text[i], "\n"))
		{
			count++;
			if (check_path_access(map->text[i]) == 1)
				return (1);
		}
	}
	if (func(count))
		return (1);
	return (0);
}
