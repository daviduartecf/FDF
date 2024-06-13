/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_helpers_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:41:43 by daduarte          #+#    #+#             */
/*   Updated: 2024/06/12 16:12:41 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	gradient(int startcolor, int endcolor, int len, int pos)
{
	float	factor[3];
	int		new[3];
	int		newcolor;

	if (len == 0)
		return (startcolor);
	factor[0] = (float)(((endcolor) >> 16) - ((startcolor) >> 16)) / (float)len;
	factor[1] = (float)(((endcolor >> 8) & 0xFF) - ((startcolor >> 8) & 0xFF))
		/ (float)len;
	factor[2] = (float)(((endcolor & 0xFF)) - ((startcolor) & 0xFF))
		/ (float)len;
	new[0] = ((startcolor) >> 16) + (pos * factor[0]);
	new[1] = ((startcolor >> 8) & 0xFF) + (pos * factor[1]);
	new[2] = ((startcolor) & 0xFF) + (pos * factor[2]);
	newcolor = ((new[0] << 16) + ((new[1] << 8)) + new[2]);
	return (newcolor);
}

void	get_min_max_altitude(t_map *map, int *min_z, int *max_z)
{
	int	y;
	int	x;

	*min_z = INT_MAX;
	*max_z = INT_MIN;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width[y])
		{
			if (map->map[y][x].z < *min_z)
				*min_z = map->map[y][x].z;
			if (map->map[y][x].z > *max_z)
				*max_z = map->map[y][x].z;
			x ++;
		}
		y ++;
	}
}

int	get_steps(t_coord p0, t_coord p1, t_line line)
{
	int	steps;

	steps = 0;
	while (1)
	{
		if (p0.x == p1.x && p0.y == p1.y)
			break ;
		line.e2 = 2 * line.e;
		if (line.e2 > -line.dy)
		{
			line.e -= line.dy;
			p0.x += line.sx;
		}
		if (line.e2 < line.dx)
		{
			line.e += line.dx;
			p0.y += line.sy;
		}
		steps ++;
	}
	return (steps);
}
