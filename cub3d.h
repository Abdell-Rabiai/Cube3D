/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:11:33 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/07/13 17:40:01 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include "get_next_line/get_next_line.h"
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
	char	**map;
	char	**text;
	int		columns;
	char    **paths;
	int		rows;
	int		text_rows;
	int     ceil_color;
	int     floor_color;
}				t_map;

/***--------------- PARSING FUNCTINOS ---------------***/
int first_string_len(char *str);
int read_data(char **argv, t_map *map);
int	count_map_lines(char **argv);
int	count_text_lines(char **argv);
void initialize_map(t_map *map, char **argv);
void free_map(t_map *map);
void print_map(t_map *map);

int	get_ceil_floor_cols(char *line);
int which_dir(char *dir);

int is_valid_map_line(char *line);
int check_invalid_characters(int fd);
int check_file_errors(char **argv, int argc);

int check_right(char **arr, int i, int j);
int check_left(char **arr, int i, int j);
int check_up(char **arr, int i, int j);
int check_down(char **arr, int i, int j);
int check_is_closed(t_map *map);
int check_multiple_players(t_map *map);