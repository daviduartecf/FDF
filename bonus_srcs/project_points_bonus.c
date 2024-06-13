/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_points_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:38:10 by daduarte          #+#    #+#             */
/*   Updated: 2024/06/13 09:48:30 by daduarte         ###   ########.fr       */
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
	int			len;
	t_coord		point;
	t_angles	angles;

	len = data->max_z - data->min_z;
	point.x = (int)(x * data->scale);
	point.y = (int)(y * data->scale);
	point.z = (int)(z * data->scale);
	angles.angle_x = data->angle_x * M_PI / 180;
	angles.angle_y = data->angle_y * M_PI / 180;
	angles.angle_z = data->angle_z * M_PI / 180;
	rotate_x(&point, angles.angle_x);
	rotate_y(&point, angles.angle_y);
	rotate_z(&point, angles.angle_z);
	point.x += data->offx;
	point.y += data->offy;
	if (data->boundaries_check == 0)
		point.color = gradient(data->color1, data->color2, len,
				abs(data->map->map[y / 20][x / 20].z));
	return (point);
}
