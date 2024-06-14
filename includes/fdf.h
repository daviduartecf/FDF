/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:59:14 by daduarte          #+#    #+#             */
/*   Updated: 2024/06/13 11:41:44 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <X11/X.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <X11/keysym.h>
# include "../gnl/get_next_line.h"
# include "../minilibx-linux/mlx.h"
# include "../ft_printf/includes/libft.h"
# include "../ft_printf/includes/ft_printf.h"

# define HEIGHT 700
# define WIDTH 860
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5
# define GRID_SIZE 20
# define Z_FACTOR 5
# define ZOOM_FACTOR 1.05

typedef struct s_boundaries
{
	int		max_x;
	int		max_y;
	int		min_x;
	int		min_y;
}	t_boundaries;

typedef struct s_line
{
	int		e;
	int		e2;
	int		sx;
	int		sy;
	int		dx;
	int		dy;
	int		steps;
}	t_line;

typedef struct s_img
{
	int		endian;
	int		line_len;
	void	*img_ptr;
	char	*img_pixels_ptr;
	int		bits_per_pixel;
}	t_img;

typedef struct s_pt
{
	int		z;
	int		color;
}	t_pt;

typedef struct s_map
{
	t_pt	**map;
	int		height;
	int		*width;
	int		max_width;
	int		color_flag;
}	t_map;

typedef struct s_coord
{
	int		x;
	int		y;
	int		z;
	int		color;
	int		true_x;
	int		true_y;
}	t_coord;

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
}	t_point;

typedef struct s_points
{
	int		x0;
	int		x1;
	int		y0;
	int		y1;
}	t_points;

typedef struct s_angles
{
	double	angle_x;
	double	angle_y;
	double	angle_z;
}	t_angles;

typedef struct s_mlx_data
{
	t_img			img;
	t_map			*map;
	int				offx;
	int				offy;
	int				max_z;
	int				min_z;
	int				color;
	double			scale;
	t_coord			**grid;
	int				height;
	int				*width;
	int				last_x;
	int				last_y;
	int				last_z;
	int				rotate;
	int				color1;
	int				color2;
	double			angle_x;
	double			angle_y;
	double			angle_z;
	double			degrees;
	int				no_scale;
	void			*mlx_ptr;
	void			*win_ptr;
	double			z_factor;
	int				show_help;
	int				max_width;
	int				win_width;
	int				win_height;
	int				first_call;
	int				is_dragging;
	int				translate_y;
	int				translate_x;
	t_boundaries	*boundaries;
	t_boundaries	*raw_boundaries;
	int				boundaries_check;
	t_boundaries	*scaled_boundaries;
}				t_mlx_data;

/* FUNCTIONS */

/* DATA INIT */

void	data_init(t_mlx_data *data, t_map *map);
void	map_init(t_map *map, int height, int *width);

/* BOUNDARIES FUNCTIONS */

void	calculate_boundaries(t_mlx_data *data);
void	set_boundaries(t_mlx_data *data, int x, int y);
void	set_each_boundary(t_mlx_data *data, t_coord point);

/* HOOK FUNCTIONS */

int		loop_hook(t_mlx_data *data);
int		close_win(t_mlx_data *data);
void	projections(int keysym, t_mlx_data *data);
int		handle_input(int keysym, t_mlx_data *data);
void	image_destroy_and_create(t_mlx_data *data);
void	handle_rotate(int keysym, t_mlx_data *data);
int		handle_z_factor(int keysym, t_mlx_data *data);
void	handle_translate(int keysym, t_mlx_data *data);
int		handle_mouse_move(int x, int y, t_mlx_data *data);
int		handle_mouse_press(int button, int x, int y, t_mlx_data *data);
int		handle_mouse_release(int button, int x, int y, t_mlx_data *data);
int		zoom_up_down(t_mlx_data *data, double max, double min, int button);

/* MISC HELPERS FUNCTIONS */

int		get_digit(char c);
int		ft_isdigit(int c);
int		is_fdf_file(char *s);
void	free_map(t_map *map);
int		array_len(char **arr);
int		ft_atoibase_fdf(char *str);
void	free_array(char **array, int k);
int		get_max_value(int *width, int height);
void	initialize_array(int *array, int size);
int		error_management(int argc, char **argv);
char	**ft_strarrayjoin(char **arr1, char **arr2);
int		calculate_offset(t_mlx_data *data, int flag);
void	ft_copy_array(char **result, char **arr1, int len);
void	*return_null(t_map *map, char **big_str, int flag);

/* READ FILES FUNCTIONS */

t_map	*read_map(char *filename);
t_pt	**allocate_map(int *width, int height);
int		map_width(char *line, char ***big_str);
t_pt	**read_map_lines(char *filename, t_map *map, char **big_str);
void	get_altitude_and_color(char *str, t_pt *point, int *color_flag);
t_pt	**atoi_loop(char **strings, int *width, int height, int *color_flag);
double	calculate_scale_factor(t_mlx_data data, int win_width, int win_height);

/* PROJECTION + ROTATION FUNCTIONS */

void	rotate_x(t_coord *p, double angle);
void	rotate_y(t_coord *p, double angle);
void	rotate_z(t_coord *p, double angle);
t_coord	project_point(int x, int y, int z, t_mlx_data *data);

/* COLOR FUNCTIONS */

int		get_steps(t_coord p0, t_coord p1, t_line line);
void	get_min_max_altitude(t_map *map, int *min_z, int *max_z);
int		gradient(int startcolor, int endcolor, int len, int pos);

/* DRAW FUNCTIONS */

void	line_math(t_coord *p0, t_line *line);
void	draw_map(t_mlx_data *data, t_map *map);
void	draw_loop(t_mlx_data *data, t_point i, t_point p);
void	draw_line(t_mlx_data *data, t_coord p0, t_coord p1);
void	put_pixel_to_image(t_img *img, int x, int y, int color);
void	get_points_to_line(t_mlx_data *data, t_point i, t_point p);
void	draw_to_image(t_mlx_data *data, t_coord p0, t_coord p1, t_line line);

/* HELPER FUNCTIONS */

void	calculate_boundaries(t_mlx_data *data);
void	set_boundaries(t_mlx_data *data, int x, int y);

/* INSTRUCTIONS FUNCTIONS */

void	call_instructions(t_mlx_data *data);
void	display_instructions(t_mlx_data *data);

/* SPLIT FUNCTIONS */

void	free_array(char **array, int k);
char	**ft_split_fdf(char const *s, char c, int *width);

#endif
