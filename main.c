/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:11:30 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/07/14 11:50:11 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
	t_map map;

	initialize_map(&map, argv);
	if (check_file_errors(argv, argc))
		return (1);
	read_textures_colors(&map, argv);
	read_map(&map, argv);
	if (check_map(&map) || check_text(&map))
		return (1);
	// if everything is ok store map and text and print everything
	store_paths_colors(&map);
	print_map(&map);
	// start_the_game(&map);
	free_map(&map);
	// while (1);
}
