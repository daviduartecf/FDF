/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_points.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:38:10 by daduarte          #+#    #+#             */
/*   Updated: 2024/06/06 13:19:11 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/* ROTATION MATRICES

Rx(angle) = {1, 0, 0}
			{0, cos(angle), -sin(angle)}
			{0, sin(angle), cos(angle)}

Ry(angle) = {cos(angle, 0, sin(angle))}
			{0, 1, 0}
			{-sin(angle, 0, cos(angle))}

Rz(angle) = {cos(angle, -sin(angle, 0))}
			{sin(angle, cos(angle, 0))}
			{0, 0, 1}*/

void	rotate_x(t_coord *p, double angle)
{
	int	tmp_y;

	tmp_y = p->y;
	p->y = (int)(tmp_y * cos(angle) - p->z * sin(angle));
	p->z = (int)(tmp_y * sin(angle) + p->z * cos(angle));
}

void	rotate_y(t_coord *p, double angle)
{
	int	tmp_x;

	tmp_x = p->x;
	p->x = (int)(tmp_x * cos(angle) + p->z * sin(angle));
	p->z = (int)(-tmp_x * sin(angle) + p->z * cos(angle));
}

void	rotate_z(t_coord *p, double angle)
{
	int	tmp_x;

	tmp_x = p->x;
	p->x = (int)(tmp_x * cos(angle) - p->y * sin(angle));
	p->y = (int)(tmp_x * sin(angle) + p->y * cos(angle));
}

t_coord	project_point(int x, int y, int z, t_mlx_data *data)
{
	int		len;
	int		color;
	t_coord	point;
	double	angle_x;
	double	angle_y;
	double	angle_z;

	len = data->max_z - data->min_z;
	point.x = (int)(x * data->scale);
	point.y = (int)(y * data->scale);
	point.z = (int)(z * data->scale);
	angle_x = data->angle_x * M_PI / 180;
	angle_y = data->angle_y * M_PI / 180;
	angle_z = data->angle_z * M_PI / 180;
	rotate_x(&point, angle_x);
	rotate_y(&point, angle_y);
	rotate_z(&point, angle_z);
	point.x += data->offx;
	point.y += data->offy;
	if (data->boundries_check == 0)
		point.color = gradient(data->color1, data->color2, len, abs(data->map->map[y/20][x/20].z));
	return (point);
}