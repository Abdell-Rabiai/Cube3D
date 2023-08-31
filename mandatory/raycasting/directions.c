/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:47:31 by arabiai           #+#    #+#             */
/*   Updated: 2023/08/30 18:51:02 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_ray_facing_right_dir(double ray_angle)
{
	return (ray_angle < 0.5 * M_PI || ray_angle > 1.5 * M_PI);
}

int	is_ray_facing_left_dir(double ray_angle)
{
	return (!is_ray_facing_right_dir(ray_angle));
}

int	is_ray_facing_down_dir(double ray_angle)
{
	return (ray_angle > 0 && ray_angle < M_PI);
}

int	is_ray_facing_up_dir(double ray_angle)
{
	return (!is_ray_facing_down_dir(ray_angle));
}

double	dist_be2n_pts(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)));
}
