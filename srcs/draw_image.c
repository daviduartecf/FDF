/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:44:24 by daduarte          #+#    #+#             */
/*   Updated: 2024/06/12 12:05:57 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	draw_to_image(t_mlx_data *data, t_coord p0, t_coord p1, t_line line)
{
	int	k;
	int	color;

	k = 0;
	while (1)
	{
		if (data->map->color_flag == 0)
		{
			color = gradient(p0.color, p1.color, line.steps, k);
			k ++;
		}
		else
			color = data->map->map[p0.true_y][p0.true_x].color;
		put_pixel_to_image(&data->img, p0.x, p0.y, color);
		if (p0.x == p1.x && p0.y == p1.y)
			break ;
		line.e2 = 2 * line.e;
		line_math(&p0, &line);
	}
}

void	draw_line(t_mlx_data *data, t_coord p0, t_coord p1)
{
	t_line	line;

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
	line.steps = get_steps(p0, p1, line);
	draw_to_image(data, p0, p1, line);
}

void	get_points_to_line(t_mlx_data *data, t_point i, t_point p)
{
	t_coord	p0;
	t_coord	p1;

	p0 = project_point(i.x, i.y, data->map->map[p.y][p.x].z, data);
	p0.true_x = p.x;
	p0.true_y = p.y;
	if (p.x + 1 < (data->map->width[p.y]))
	{
		p1 = project_point(i.x + GRID_SIZE, i.y,
				data->map->map[p.y][p.x + 1].z, data);
		draw_line(data, p0, p1);
	}
	if (p.y + 1 < (data->map->height) && (p.x < data->map->width[p.y + 1]))
	{
		p1 = project_point(i.x, i.y + GRID_SIZE,
				data->map->map[p.y + 1][p.x].z, data);
		draw_line(data, p0, p1);
	}
}

void	draw_loop(t_mlx_data *data, t_point i, t_point p)
{
	while (i.y < (((data->map->height) * GRID_SIZE)))
	{
		p.x = 0;
		i.x = 0;
		while (i.x < (((data->map->width[p.y]) * GRID_SIZE)))
		{
			get_points_to_line(data, i, p);
			p.x ++;
			i.x += GRID_SIZE;
		}
		p.y ++;
		i.y += GRID_SIZE;
	}
}

void	draw_map(t_mlx_data *data, t_map *map)
{
	t_point		index;
	t_point		point;

	point.x = 0;
	point.y = 0;
	index.x = 0;
	index.y = 0;
	if (map->color_flag == 0)
		get_min_max_altitude(map, &data->min_z, &data->max_z);
	calculate_boundaries(data);
	if (data->no_scale == 1)
	{
		data->scale = calculate_scale_factor(*data, WIDTH, HEIGHT);
		data->no_scale = 0;
	}
	data->offx = (WIDTH - (data->boundaries->max_x - data->boundaries->min_x))
		/ 2 - data->boundaries->min_x + data->translate_x;
	data->offy = (HEIGHT - (data->boundaries->max_y - data->boundaries->min_y))
		/ 2 - data->boundaries->min_y + data->translate_y;
	draw_loop(data, index, point);
	data->offx = 0;
	data->offy = 0;
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.img_ptr, 0, 0);
	data->first_call = 1;
}
