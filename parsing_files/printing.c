/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:02:27 by arabiai           #+#    #+#             */
/*   Updated: 2023/07/14 11:03:04 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void print_only_map(t_map *map)
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
		printf("(%s)\n", map->map[i]);
}
