/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:11:33 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/07/11 08:31:49 by arabiai          ###   ########.fr       */
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

int read_data(char **argv, t_map *map);
int	count_map_lines(char **argv);
void initialize_map(t_map *map, char **argv);
void free_map(t_map *map);
int	count_map_lines(char **argv);
int read_data(char **argv, t_map *map);
void print_map(t_map *map);
int	get_ceil_floor_cols(char *line);
int which_dir(char *dir);