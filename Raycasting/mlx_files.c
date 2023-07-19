/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 05:14:45 by arabiai           #+#    #+#             */
/*   Updated: 2023/07/19 05:15:05 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
  char    *dst;

  dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
  *(unsigned int*)dst = color;
}