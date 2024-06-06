/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:44:24 by daduarte          #+#    #+#             */
/*   Updated: 2024/06/06 15:49:38 by daduarte         ###   ########.fr       */
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

void	draw_to_image(t_mlx_data *data, t_coord p0, t_coord p1, t_line line, t_point p, int steps)
{
	int	k;
	int	color;

	k = 0;
	while (1)
	{
		if (data->map->color_flag == 0)
		{
			color = gradient(p0.color, p1.color, steps, k);
			k ++;
		}
		else
			color = data->map->map[p.y][p.x].color;
		put_pixel_to_image(&data->img, p0.x, p0.y, color);
		if (p0.x == p1.x && p0.y == p1.y)
			break ;
		line.e2 = 2 * line.e;
		line_math(&p0, &line);
	}
}

void	draw_line(t_mlx_data *data, t_coord p0, t_coord p1, t_point p)
{
	t_line	line;
	int	steps;

	if (p0.x < p1.x)
		line.sx = 1;
	else
		line.sx = -1;
	if (p0.y < p1.y)
		line.sy = 1;
	else
		line.sy = -1;
	line.dx = abs(p1.x - p0.x);
	line.dy = abs(p1.y - p0.y);
	line.e = line.dx - line.dy;
	steps = get_steps(*data, p0, p1, line);
	draw_to_image(data, p0, p1, line, p, steps);
}

void	draw_loop(t_mlx_data *data)
{
	t_coord	p0;
	t_coord	p1;
	t_point	i, p;

	p.x = 0;
	p.y = 0;
	i.x = 0;
	i.y = 0;
	while (i.y < (((data->map->height) * GRID_SIZE)))
	{
		p.x = 0;
		i.x = 0;
		while (i.x < (((data->map->width[p.y]) * GRID_SIZE)))
		{
			p0 = project_point(i.x, i.y, data->map->map[p.y][p.x].z, data);
			if (p.x + 1 < (data->map->width[p.y]))
			{
				p1 = project_point(i.x + GRID_SIZE, i.y, data->map->map[p.y][p.x + 1].z, data);
				draw_line(data, p0, p1, p);
			}
			if (p.y + 1 < (data->map->height) && (p.x < data->map->width[p.y + 1]))
			{
				p1 = project_point(i.x, i.y + GRID_SIZE, data->map->map[p.y + 1][p.x].z, data);
				draw_line(data, p0, p1, p);
			}
			p.x ++;
			i.x += GRID_SIZE;
		}
		printf("DRAW LINE %d----\n", p.y);
		p.y ++;
		i.y += GRID_SIZE;
	}
}

void	draw_map(t_mlx_data *data, t_map *map)
{
	t_point		index;
	t_point		point;
	t_point		p1;

	point.x = 0;
	point.y = 0;
	index.x = 0;
	index.y = 0;
	if (map->color_flag == 0)
		get_min_max_altitude(map, &data->min_z, &data->max_z);
	calculate_boundries(data);
	printf("here\n");
	data->offx = (WIDTH - (data->boundries->max_x - data->boundries->min_x))
		/ 2 - data->boundries->min_x;
	data->offy = (HEIGHT - (data->boundries->max_y - data->boundries->min_y))
		/ 2 - data->boundries->min_y;
	draw_loop(data);
	data->offx = 0;
	data->offy = 0;
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.img_ptr, 0, 0);
	data->first_call = 1;
}
