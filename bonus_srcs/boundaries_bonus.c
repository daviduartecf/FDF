/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boundaries.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:45:19 by daduarte          #+#    #+#             */
/*   Updated: 2024/06/12 11:46:00 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	set_each_boundary(t_mlx_data *data, t_coord point)
{
	if (point.x > data->boundaries->max_x)
		data->boundaries->max_x = point.x;
	if (point.y > data->boundaries->max_y)
		data->boundaries->max_y = point.y;
	if (point.x < data->boundaries->min_x)
		data->boundaries->min_x = point.x;
	if (point.y < data->boundaries->min_y)
		data->boundaries->min_y = point.y;
}

void	set_boundaries(t_mlx_data *data, int x, int y)
{
	t_coord	point;
	t_point	point2;

	point2.x = 0;
	point2.y = 0;
	data->boundaries_check = 1;
	while (point2.y < (data->map->height * GRID_SIZE))
	{
		x = 0;
		point2.x = 0;
		if (y >= data->map->height)
			break ;
		while (point2.x < (data->map->width[y] * GRID_SIZE))
		{
			if (x >= data->map->width[y])
				break ;
			point = project_point(point2.x, point2.y,
					data->map->map[y][x].z, data);
			set_each_boundary(data, point);
			x++;
			point2.x += GRID_SIZE;
		}
		point2.y += GRID_SIZE;
	}
	data->boundaries_check = 0;
}

void	calculate_boundaries(t_mlx_data *data)
{
	int		x;
	int		y;

	data->boundaries->min_x = INT_MAX;
	data->boundaries->max_x = INT_MIN;
	data->boundaries->min_y = INT_MAX;
	data->boundaries->max_y = INT_MIN;
	y = 0;
	x = 0;
	set_boundaries(data, x, y);
}
