/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_text.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:20:11 by arabiai           #+#    #+#             */
/*   Updated: 2023/07/14 11:48:05 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_path_access(char *str)
{
	char	*sub;
	char	*trim;
	
	trim = ft_strtrim(str + 2, " .\n");
	sub = ft_substr(trim, 0, word_length(trim, ' '), 1);
	if (access(sub, F_OK) != 0)
	{
		printf("Error\n");
		printf("Texture path not accessible\n");
		printf("path => %s\n", sub);
		free(sub);
		return (1);
	}
	free(sub);
	return (0);
}

int check_text(t_map *map)
{
	char **text;
	int i;

	text = map->text;
	i = 0;
	while (text[i])
	{
		if ((!ft_strncmp(text[i], "F", 1) || !ft_strncmp(text[i], "C", 1)) && ft_strcmp(text[i], "\n"))
		{
			if (get_ceil_floor_cols(text[i]) == -1)
				return (printf("Error\nInvalid color\n"), 1);
		}
		else if (which_dir(text[i]) == -1 && ft_strcmp(text[i], "\n"))
			return (printf("Error\nInvalid texture path\n"), 1);
		else if (which_dir(text[i]) != -1 && ft_strcmp(text[i], "\n"))
		{
			if (check_path_access(text[i]) == 1)
				return (1);
		}
		i++;
	}
	return 0;
}
