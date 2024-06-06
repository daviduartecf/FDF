/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:59:14 by daduarte          #+#    #+#             */
/*   Updated: 2024/06/06 17:44:57 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "../gnl/get_next_line.h"
# include <unistd.h>
#include <math.h>
#include <limits.h>

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

typedef struct s_boundries
{
	int	max_x;
	int	max_y;
	int	min_x;
	int	min_y;
}	t_boundries;

typedef struct s_line
{
	int	sx;
	int	sy;
	int	dx;
	int	dy;
	int	e;
	int	e2;
}	t_line;

typedef struct s_img
{
	void	*img_ptr;
	char	*img_pixels_ptr;
	int	bits_per_pixel;
	int	endian;
	int	line_len;
}	t_img;

typedef struct s_pt
{
	int	z;
	int	color;
}	t_pt;

typedef struct s_map
{
	t_pt	**map;
	int	height;
	int	*height_array;
	int	*width;
	int	max_width;
	int	color_flag;
}	t_map;

typedef struct		s_coord
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_coord;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
}	t_point;

typedef struct s_points
{
	int x0;
	int x1;
	int y0;
	int y1;
}	t_points;

typedef struct	s_mlx_data {
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	int	offx;
	int	offy;
	int height;
	int *width;
	double degrees;
	t_map *map;
	int	rotation_axis;
	double angle_x;
	double angle_y;
	double angle_z;
	int is_dragging;
	int last_x;
	int last_y;
	int last_z;
	int	rotate;
	int	first_call;
	double	scale;
	int	color1;
	int	color2;
	int	color;
	int	max_z;
	int	min_z;
	int	boundries_check;
	t_coord	**grid;
	t_boundries	*boundries;
}				t_mlx_data;

/* FUNCTIONS */

/* READ FILES FUNCTIONS */

t_map	*read_map(char *filename);
t_pt	**read_map_lines(char *filename, t_map *map, char **big_str);
int	map_width(char *line, char ***big_str);
int	get_max_value(int *width, int height);
void	free_map(t_map *map);
int	ft_atoi(char *str);
t_pt	**atoi_loop(char **strings, int *width, int height, int *color_flag);
char	*ft_strchr(char *s, int c);
int	get_digit(char c);
int	ft_atoibase_fdf(char *str);
void	get_altitude_and_color(char *str, t_pt *point, int *color_flag);
int	ft_isdigit(int c);
t_pt	**allocate_map(int *width, int height);
char	*ft_strdup(char *s);

/* PROJECTION + ROTATION FUNCTIONS */

void	rotate_x(t_coord *p, double angle);
void	rotate_y(t_coord *p, double angle);
void	rotate_z(t_coord *p, double angle);
t_coord	project_point(int x, int y, int z, t_mlx_data *data);

/* COLOR FUNCTIONS */

void	get_min_max_altitude(t_map *map, int *min_z, int *max_z);
int		gradient(int startcolor, int endcolor, int len, int pos);
int		get_steps(t_mlx_data data, t_coord p0, t_coord p1, t_line line);

/* DRAW FUNCTIONS */

void	draw_loop(t_mlx_data *data);
void	put_pixel_to_image(t_img *img, int x, int y, int color);
void	draw_to_image(t_mlx_data *data, t_coord p0, t_coord p1, t_line line, t_point p, int steps);
void	draw_line(t_mlx_data *data, t_coord p0, t_coord p1, t_point p);
void	draw_map(t_mlx_data *data, t_map *map);

/* HELPER FUNCTIONS */

void	calculate_boundries(t_mlx_data *data);
void	set_boundries(t_boundries *boundries, t_mlx_data *data, int x, int y);

/* SPLIT FUNCTIONS */

char	**ft_split(char const *s, char c, int *width);
void	free_array(char **array, int k);

# define HEIGHT 1000
# define WIDTH 1000
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5
# define GRID_SIZE 20

#endif
