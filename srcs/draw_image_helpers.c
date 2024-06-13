/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:11:07 by daduarte          #+#    #+#             */
/*   Updated: 2024/06/12 14:34:01 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	put_pixel_to_image(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		pixel_index;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel_index = (y * img->line_len) + (x * (img->bits_per_pixel / 8));
	pixel = img->img_pixels_ptr + pixel_index;
	*(unsigned int *)pixel = color;
}

void	line_math(t_coord *p0, t_line *line)
{
	if (line->e2 > -line->dy)
	{
		line->e -= line->dy;
		p0->x += line->sx;
	}
	if (line->e2 < line->dx)
	{
		line->e += line->dx;
		p0->y += line->sy;
	}
}

void	free_array(char **array, int k)
{
	if (!array)
	{
		free(array);
		return ;
	}
	while (k >= 0)
	{
		free(array[k]);
		k --;
	}
	free(array);
}

double	calculate_scale_factor(t_mlx_data data, int win_width, int win_height)
{
	double	scale_x;
	double	scale_y;
	int		map_width;
	int		map_height;

	map_width = data.boundaries->max_x - data.boundaries->min_x;
	map_height = data.boundaries->max_y - data.boundaries->min_y;
	scale_x = (double)(win_width - 20) / map_width;
	scale_y = (double)(win_height - 20) / map_height;
	if (scale_x < scale_y)
		return (scale_x);
	else
		return (scale_y);
}
