/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:11:33 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/08/14 19:39:57 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <stdbool.h>
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include "new_mlx/mlx.h"

# define SCALE 32
# define WIDTH 1000
# define HEIGHT 800
# define PIE 3.14159265358979323846
# define FAR_FROM_WALL 4
# define WINDOW_WIDTH 1920*3/2
# define WINDOW_HEIGHT 1080*3/2
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
	double	WallHitX;
	double	WallHitY;
	double	distance;
	bool	wasHitVertic;
	double	xintercept;
	double	yintercept;
	double	xstep;
	double	ystep;
	bool	HorzWallHit;
	double	HorzWallHitX;
	double	HorzWallHitY;
	double	nextHorzTouchX;
	double 	nextHorzTouchY;
	double 	nextVertTouchX;
	double 	nextVertTouchY;
	double 	HorzHitDistance;
	double 	vertHitDistance;
	bool 	vertWallHit;
	double 	vertWallHitX;
	double 	vertWallHitY;
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
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
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
	int 		e2;
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
	double 		turn_dir; // right or left
	double		walk_dir; // forward or backward
	double		rotation_angel;
	double 		move_speed;
	double 		rotation_speed;
	int			dir;
}				t_player;

typedef struct cords
{
	double x;
	double y;
}				t_cords;

typedef struct s_map
{
	void		*mlx_ptr;
	void		*window_ptr;
	char		**map;
	char		**text;
	char    	**paths;
	int			text_rows;
	int     	ceil_color;
	int     	floor_color;
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
}				t_map;


/***--------------- INIT FUNCTIONS ---------------***/
void	initialize_map(t_map *map, char **argv);
int		count_text_lines(char **argv);
int		count_map_lines(char **argv);
size_t 	max_len(char **argv);
int		count_map_cols(char **argv);

/***--------------- PARSING FUNCTINOS ---------------***/
void	free_map(t_map *map);

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
int		key_hook(int keycode, t_map *map);
int		mouse_hook(int x, int y, t_map *map);
void	change_coordinates(t_map *map, int x2, int y2);
void	apply_the_changes(t_map *map);
int		exit_hook(t_map *map);
void	create_new_image(t_map *map, t_image *image);
void	player_movement_hooks(int keycode, t_map *map);

/***--------------- THE MAP AN PLAYER MOVEMEMET FUNCTINOS ---------------***/
int		draw_the_map(t_map *map);
void	draw_the_player(t_map *map);
void	minimap(t_map *map);
void	draw_square(t_map *map ,int x, int y, int color);
void	draw_circle(t_map *map, double centerX, double centerY, int radius, int color);
void	draw_line(t_map *map, int x1, int y1);
void	draw_bresenhams_line(t_map *carte);
// void	get_color_and_draw_sqaure(t_map *map, double i, double j);
void	draw_rays(t_map *map);
int		is_there_a_wall(t_map *map, double x, double y);
void    horizontal_intersections(t_map *map, double rayAngle, int column_id);
double	normalize_angle(double angle);
void	draw_line_till_inter(t_map *map, int x1, int y1, int x2, int y2);
void	cast_ray(t_map *map, double rayAngle);

/***------------------RAYCASTIGN-----------------------------***/
void	rect(t_map *map, int x, int y, double width, double height, int color);
int		is_ray_facing_right_dir(double rayAngle);
int		is_ray_facing_left_dir(double rayAngle);
int		is_ray_facing_down_dir(double rayAngle);
int		is_ray_facing_up_dir(double rayAngle);
void	*open_texture_files(t_map *map, int dir);
void	draw_ceiling_and_floor(t_map *map);

/*game*/
void game(t_map *map);