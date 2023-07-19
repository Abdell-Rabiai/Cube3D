/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:11:33 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/07/19 06:08:15 by arabiai          ###   ########.fr       */
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

# define SCALE 32
# define HEIGHT 1080
# define WIDTH 1920
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
	char    **paths;
	int		text_rows;
	int     ceil_color;
	int     floor_color;
	int		rows;
	int		cols;
}				t_map;

typedef struct s_image
{
  void        *img;
  char        *addr;
  int         bits_per_pixel;
  int         line_length;
  int         endian;
}				t_image;

typedef struct s_mlx_info
{
	void		*mlx_ptr;
	void		*window_ptr;
	void		*img_ptr;
	t_image		image;
}				t_mlx_info;

/***--------------- PARSING FUNCTINOS ---------------***/
void initialize_map(t_map *map, t_mlx_info *info, char **argv);
int count_text_lines(char **argv);
int	count_map_lines(char **argv);
int	count_map_cols(char **argv);
void	free_map(t_map *map);

int read_data(char **argv, t_map *map);
void read_map(t_map *map, char **argv);
int which_dir(char *dir);
void read_textures_colors(t_map *map, char **argv);
int	get_ceil_floor_cols(char *line);
void store_paths_colors(t_map *map);

void print_map(t_map *map);
void print_text(t_map *map);
void print_only_map(t_map *map);
void print_paths(t_map *map);


int is_valid_map_line(char *line);
int check_invalid_characters(char **arr);
void read_textures_colors(t_map *map, char **argv);


int check_map(t_map *map);
int check_multiple_players(char **arr);
int check_invalid_characters(char **arr);
int check_valid_map_line(char *line);

int check_text(t_map *map);
int check_file_errors(char **argv, int argc);
int check_is_closed(char **arr);
int check_right(char **arr, int i, int j);
int check_left(char **arr, int i, int j);
int check_up(char **arr, int i, int j);
int check_down(char **arr, int i, int j);
int check_multiple_players(char **arr);
void	minimap(t_map *map, t_mlx_info *mlx_info);

/***--------------- MLX FUNCTINOS ---------------***/
void	my_mlx_pixel_put(t_image *image, int x, int y, int color);

/***--------------- RAYCASTING FUNCTINOS ---------------***/