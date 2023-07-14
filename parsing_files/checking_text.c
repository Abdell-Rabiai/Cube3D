/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_text.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:20:11 by arabiai           #+#    #+#             */
/*   Updated: 2023/07/14 09:21:32 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int check_text(t_map *map)
{
	char **text;
	int i;
	char *sub;
	char *trim;

	sub = NULL;
	trim = NULL;
	text = map->text;
	i = 0;
	while (text[i])
	{
		if ((!ft_strncmp(text[i], "F", 1) || !ft_strncmp(text[i], "C", 1) ) && ft_strcmp(text[i], "\n"))
		{
			if (get_ceil_floor_cols(text[i]) == -1)
				return (printf("Error\nInvalid color\n"), 1);
		}
		else if (which_dir(text[i]) == -1 && ft_strcmp(text[i], "\n"))
			return (printf("Error\nInvalid texture path\n"), 1);
		else if (which_dir(text[i]) != -1 && ft_strcmp(text[i], "\n"))
		{
			trim = ft_strtrim(text[i] + 2, " .\n");
			sub = ft_substr(trim, 0, word_length(trim, ' '), 1);
			if (access(sub, F_OK) != 0)
			{
				printf("path = [%s]\n", sub);
				free(sub);
				return (printf("Error\nTexture path not accessible\n"), 1);
			}
			free(sub);
		}
		i++;
	}
	return 0;
}