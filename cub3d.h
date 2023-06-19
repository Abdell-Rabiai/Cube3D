/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:11:33 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/05/20 11:55:47 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include "get_next_line.h"
# include "libft/libft.h"
# include "mlx.h"

typedef enum directions
{
    NORTH,
    SOUTH,
    EAST,
    WEST
}				t_directions;

typedef struct s_map
{
    int		columns;
    char    **paths;
    int		rows;
    int     ceil_color;
    int     floor_color;
    char	**map;
}				t_map;

int pars_map(int map_fd, t_map *map);
int	count_map_lines(int	fd);