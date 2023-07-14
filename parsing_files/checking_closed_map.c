/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_closed_map.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:15:44 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/07/14 09:19:49 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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