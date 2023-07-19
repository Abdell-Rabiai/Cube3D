/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:11:30 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/07/19 05:35:19 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exit_hook(void)
{
	exit(0);
}

int	key_hook(int keycode, t_mlx_info *info)
{
	if (keycode == 53)
	{
		mlx_destroy_window(info->mlx_ptr, info->window_ptr);
		info->window_ptr = NULL;
		exit(0);
	}
	return (0);
}

void initialize_map(t_map *map, t_mlx_info *info, char **argv)
{
	t_image *image;

	image = &info->image;
	map->ceil_color = 0;
	map->floor_color = 0;
	map->rows = count_map_lines(argv);
	map->text_rows = count_text_lines(argv);
	map->map = NULL;
	map->paths = NULL;
	

	info->mlx_ptr = mlx_init();
	info->window_ptr = mlx_new_window(info->mlx_ptr, map->rows * SCALE, 33 * SCALE, "CUBE3D");
	image->img = mlx_new_image(info->mlx_ptr, WIDTH, HEIGHT);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel, &image->line_length, &image->endian);

}

int parsing(char **argv, int argc, t_map *map)
{
	if (check_file_errors(argv, argc))
		return (1);
	read_textures_colors(map, argv);
	read_map(map, argv);
	if (check_map(map) || check_text(map))
		return (1);
	store_paths_colors(map);
	print_map(map);
	return (0);
}

int main(int argc, char **argv)
{
	t_map map;
	t_mlx_info info;

	initialize_map(&map, &info, argv);
	if (parsing(argv, argc, &map))
		return (1);
	minimap(&map, &info);
	mlx_put_image_to_window(info.mlx_ptr, info.window_ptr, info.image.img, 0, 0);
	mlx_hook(info.window_ptr, 2, 0, key_hook, &info);
	mlx_hook(info.window_ptr, 17, 0, exit_hook, 0);
	mlx_loop(info.mlx_ptr);
	free_map(&map);
}
