/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:11:33 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/09/04 12:13:26 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "get_next_line/get_next_line.h"
#include "../mandatory/libft/libft.h"
#include "mlx.h"

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

typedef struct intersect
{
	double	wall_hit_x;
	double	wall_hit_y;
	double	distance;
	bool	was_hit_vertic;
	double	xintercept;
	double	yintercept;
	double	xstep;
	double	ystep;
	bool	horz_wall_hit;
	double	horz_wall_hit_x;
	double	horz_wall_hit_y;
	double	next_horz_touch_x;
	double	next_horz_touch_y;
	double	next_vert_touch_x;
	double	next_vert_touch_y;
	double	horz_hit_distance;
	double	vert_hit_distance;
	bool	vert_wall_hit;
	double	vert_wall_hit_x;
	double	vert_wall_hit_y;
}				t_intersect;

typedef enum directions
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}				t_directions;

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct s_image
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_image;

typedef struct s_bresenham
{
	int			dx;
	int			dy;
	int			err;
	int			step_x;
	int			step_y;
	int			e2;
	t_point		point1;
	t_point		point2;
}				t_bresenham;

typedef struct s_player
{
	double		x;
	double		y;
	double		previous_x;
	double		previous_y;
	double		step;
	double		turn_dir;
	double		walk_dir;
	double		translate_y;
	double		rotation_angel;
	double		move_speed;
	double		rotation_speed;
	int			dir;
}				t_player;

typedef struct cords
{
	double		x;
	double		y;
}				t_cords;

typedef struct s_map
{
	void		*mlx_ptr;
	void		*window_ptr;
	char		**map;
	char		**text;
	char		**paths;
	int			text_rows;
	int			ceil_color;
	int			floor_color;
	int			rows;
	int			y;
	int			cols;
	int			x;
	int			max_len;
	t_bresenham	*bresenham;
	t_intersect	*intersect;
	t_image		*image;
	t_image		*mini_image;
	int			mini_width;
	int			mini_height;
	int			width;
	int			height;
	t_player	*player;
	t_image		textures[5];
	t_cords		*start;
	t_cords		*end;
	double		ray_angle;
	int			cube_size;
	double		mini_x;
	double		mini_y;
	double		new_x;
	double		new_y;
	double		wall_strip_height;
	double		dist_proj_plane;
	double		ray_distance;
	int			num_rays;
	double		fov_angle;
	double		offset_x;
	double		offset_y;
}				t_map;

/***--------------- INIT FUNCTIONS ---------------***/
void	initialize_map(t_map *map, char **argv);
int		count_text_lines(char **argv);
int		count_map_lines(char **argv);
size_t	max_len(char **argv);
int		count_map_cols(char **argv);
void	protect(t_map *map);
void	init_malloc(t_map *map, char **argv);
void	init_intersect(t_map *map);
void	init_player(t_map *map);
void	init_mlx(t_map *map);

/***--------------- PARSING FUNCTINOS ---------------***/
void	free_map(t_map *map);
void	read_the_map(int map_fd, char *line, t_map *map);

int		read_data(char **argv, t_map *map);
void	read_map(t_map *map, char **argv);
int		which_dir(char *dir);
void	read_textures_colors(t_map *map, char **argv);
int		get_ceil_floor_cols(char *line);
void	store_paths_colors(t_map *map);

void	print_map(t_map *map);
void	print_text(t_map *map);
void	print_only_map(t_map *map);
void	print_paths(t_map *map);

void	make_map_rectangular_to_maxlen(t_map *map);
int		parsing(char **argv, int argc, t_map *map);
void	get_starting_position(t_map *map);
void	get_player_position(t_map *map);
void	open_textures(t_map *map);

int		is_player(char dir);
int		is_valid_map_line(char *line);
int		check_invalid_characters(char **arr);
void	read_textures_colors(t_map *map, char **argv);

int		check_map(t_map *map);
int		check_multiple_players(char **arr);
int		check_invalid_characters(char **arr);
int		check_valid_map_line(char *line);
int		check_text(t_map *map);
int		check_file_errors(char **argv, int argc);
int		check_is_closed(char **arr);
int		check_right(char **arr, int i, int j);
int		check_left(char **arr, int i, int j);
int		check_up(char **arr, int i, int j);
int		check_down(char **arr, int i, int j);
int		check_multiple_players(char **arr);

/***--------------- MLX FUNCTINOS && HOOKS FUNCTIONS ---------------***/
void	my_mlx_pixel_put(t_image *image, int x, int y, int color);
void	all_hooks(t_map *map);
int		draw_the_frame(t_map *map);
int		mouse_hook(int x, int y, t_map *map);
void	change_coordinates(t_map *map, int x2, int y2);
void	apply_the_changes(t_map *map);
int		exit_hook(t_map *map);
void	create_new_image(t_map *map, t_image *image);
int		key_pressed(int keycode, t_map *map);
int		key_released(int keycode, t_map *map);

/***--------------- THE MAP AN PLAYER MOVEMEMET FUNCTINOS ---------------***/
int		draw_the_map(t_map *map);
void	draw_the_player(t_map *map);
void	minimap(t_map *map);
void	draw_square(t_map *map, int x, int y, int color);
void	draw_circle(t_map *map);
void	draw_line(t_map *map, int x1, int y1);
void	draw_bresenhams_line(t_map *carte);

void	draw_rays(t_map *map);
int		is_there_a_wall(t_map *map, double x, double y);
int		is_wall(t_map *map, double x, double y);
void	horizontal_intersections(t_map *map, double ray_angle);
void	vertical_intersections(t_map *map, double ray_angle);
double	normalize_angle(double angle);
void	cast_ray(t_map *map, double ray_angle);
void	distance_calc(t_map *map);

/***------------------RAYCASTIGN-----------------------------***/
int		is_ray_facing_right_dir(double ray_angle);
int		is_ray_facing_left_dir(double ray_angle);
int		is_ray_facing_down_dir(double ray_angle);
int		is_ray_facing_up_dir(double ray_angle);
void	*open_texture_files(t_map *map, int dir);
void	draw_ceiling_and_floor(t_map *map);

void	draw_line_rays(t_map *map, int x1, int y1, double ray_angle);
void	draw_ceiling_and_floor(t_map *map);
int		direction(t_map *map, double ray_angle);
void	*open_texture_files(t_map *map, int dir);
int		rgba_to_int(int r, int g, int b, double a);

double	dist_be2n_pts(double x1, double y1, double x2, double y2);
void	assign_wall_hit_cords(t_map *map, bool is_vertic);
/*game*/
void	game(t_map *map);