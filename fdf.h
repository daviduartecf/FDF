/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:59:14 by daduarte          #+#    #+#             */
/*   Updated: 2024/05/21 16:33:07 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "gnl/get_next_line.h"
# include <unistd.h>

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

typedef struct s_img
{
	void	*img_ptr;
	char	*img_pixels_ptr;
	int	bits_per_pixel;
	int	endian;
	int	line_len;
}	t_img;

typedef struct s_map
{
	int	**map;
	int	height;
	int	width;
}	t_map;

typedef struct s_point
{
	int	x;
	int	y;
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
	int width;
}				t_mlx_data;

int	**read_map_lines(char *filename, t_map *map);
t_map	*read_map(char *filename);
char	**ft_split(char const *s, char c);

# define HEIGHT 500
# define WIDTH 500
# define IMG_HEIGHT 250
# define IMG_WIDTH 250

#endif
