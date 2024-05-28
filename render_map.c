/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:10:41 by daduarte          #+#    #+#             */
/*   Updated: 2024/05/28 15:54:54 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <limits.h>

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

void	rotate_x(t_point *p, double angle)
{
	int	tmp_y;

	tmp_y = p->y;
	p->y = (int)(tmp_y * cos(angle) - p->z * sin(angle));
	p->z = (int)(tmp_y * sin(angle) + p->z * cos(angle));
}

void	rotate_y(t_point *p, double angle)
{
	int	tmp_x;

	tmp_x = p->x;
	p->x = (int)(tmp_x * cos(angle) + p->z * sin(angle));
	p->z = (int)(-tmp_x * sin(angle) + p->z * cos(angle));
}

void	rotate_z(t_point *p, double angle)
{
	int	tmp_x;

	tmp_x = p->x;
	p->x = (int)(tmp_x * cos(angle) - p->y * sin(angle));
	p->y = (int)(tmp_x * sin(angle) + p->y * cos(angle));
}

/* t_point	project_point(int x, int y, int z, t_mlx_data *data)
{
	t_point	point;
	double	angle_x;
	double	angle_y;
	double	angle_z;

	point.x = x;
	point.y = y;
	point.z = z;
	angle_x = data->angle_x * M_PI / 180;
	angle_y = data->angle_y * M_PI / 180;
	angle_z = data->angle_z * M_PI / 180;
	rotate_x(&point, angle_x);
	rotate_y(&point, angle_y);
	rotate_z(&point, angle_z);
	point.x += data->offx;
	point.y += data->offy;
	return (point);
} */

t_point	project_point(int x, int y, int z, t_mlx_data *data)
{
	t_point	point;

	point.x = ((x - y) * cos(M_PI / 6)) + data->offx; // 30 degrees
	point.y = ((x + y) * sin(M_PI / 6) - z) + data->offy;
	return (point);
}

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

void	set_boundries(t_boundries *boundries, t_mlx_data *data, int x, int y)
{
	t_point	point;
	t_point	point2;

	point2.x = 0;
	point2.y = 0;
	while (point2.y < data->map->height * 15)
	{
		x = 0;
		while (point2.x < data->map->width * 15)
		{
			point = project_point(point2.x, point2.y, data->map->map[y][x], data);
			if (point.x > boundries->max_x)
				boundries->max_x = point.x;
			if (point.y > boundries->max_y)
				boundries->max_y = point.y;
			if (point.x < boundries->min_x)
				boundries->min_x = point.x;
			if (point.y < boundries->min_y)
				boundries->min_y = point.y;
			x++;
			point2.x += 15;
		}
		y ++;
		point2.y += 15;
	}
}

void	calculate_boundries(t_boundries *boundries, t_mlx_data *data)
{
	int		x;
	int		y;

	boundries->min_x = INT_MAX;
	boundries->max_x = INT_MIN;
	boundries->min_y = INT_MAX;
	boundries->max_y = INT_MIN;
	y = 0;
	x = 0;
	set_boundries(boundries, data, x, y);
}

void	draw_to_image(t_mlx_data *data, t_point p0, t_point p1, t_line line)
{
	while (1)
	{
		put_pixel_to_image(&data->img, p0.x, p0.y, 0xfffff00);
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
	}
}

void	draw_line(t_mlx_data *data, t_point p0, t_point p1)
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
	draw_to_image(data, p0, p1, line);
}

/* void	draw_grid(t_mlx_data *data)
{
	draw_line(data, WIDTH/2, 0, WIDTH/2, HEIGHT);
	draw_line(data, 0, HEIGHT/2, WIDTH, HEIGHT/2);
	draw_line(data, WIDTH, 0, 0, HEIGHT);
} */

void	draw_loop(t_mlx_data *data, t_point p, t_point i, t_point p1)
{
	t_point	p0;

	while (i.y < (((data->map->height) * 15)))
	{
		p.x = 0;
		i.x = 0;
		while (i.x < (((data->map->width) * 15)))
		{
			p0 = project_point(i.x, i.y, data->map->map[p.y][p.x], data);
			if (i.x + 15 < (((data->map->width) * 15)))
			{
				p1 = project_point(i.x + 15, i.y, data->map->map[p.y][p.x + 1], data);
				draw_line(data, p0, p1);
			}
			if (i.y + 15 < (((data->map->height) * 15)))
			{
				p1 = project_point(i.x, i.y + 15, data->map->map[p.y + 1][p.x], data);
				draw_line(data, p0, p1);
			}
			p.x ++;
			i.x += 15;
		}
		p.y ++;
		i.y += 15;
	}
}

void	draw_map(t_mlx_data *data, t_map *map)
{
	t_boundries	boundries;
	t_point		index;
	t_point		point;
	t_point		p1;

	point.x = 0;
	point.y = 0;
	index.x = 0;
	index.y = 0;
	//calculate offset based on dimensions of rotated grid
	calculate_boundries(&boundries, data);
	data->offx = (WIDTH - (boundries.max_x - boundries.min_x))
		/ 2 - boundries.min_x;
	data->offy = (HEIGHT - (boundries.max_y - boundries.min_y))
		/ 2 - boundries.min_y;
	draw_loop(data, point, index, p1);
	data->offx = 0;
	data->offy = 0;
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.img_ptr, data->offx, data->offy);
}

int	handle_input(int keysym, t_mlx_data *data)
{
	if (keysym == XK_w)
		data->angle_x += 5;
	else if (keysym == XK_s)
		data->angle_x -= 5;
	else if (keysym == XK_d)
		data->angle_y += 5;
	else if (keysym == XK_a)
		data->angle_y -= 5;
	else if (keysym == XK_Escape)
	{
		printf("Key %d ESQ has been pressed\n\n", keysym);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit(1);
	}
	printf("Key %d has been pressed\n\n", keysym);
	printf("Degree:%f \n\n", data->degrees);
	mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	data->img.img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->img.img_pixels_ptr = mlx_get_data_addr(data->img.img_ptr,
			&data->img.bits_per_pixel, &data->img.line_len, &data->img.endian);
	draw_map(data, data->map);
	return (0);
}

int	handle_mouse_press(int button, int x, int y, t_mlx_data *data)
{
	if (button == 1)
	{
		data->is_dragging = 1;
		data->last_x = x;
		data->last_y = y;
	}
	return (0);
}

int	handle_mouse_release(int button, int x, int y, t_mlx_data *data)
{
	if (button == 1)
		data->is_dragging = 0;
	return (0);
}

int	handle_mouse_move(int x, int y, t_mlx_data *data)
{
	int	dx;
	int	dy;

	if (data->is_dragging)
	{
		dx = x - data->last_x;
		dy = y - data->last_y;
		data->angle_x += dx * 0.07;
		data->angle_y += dy * 0.07;
		data->angle_z += (dx + dy) * 0.07;
		data->last_x = x;
		data->last_y = y;
		mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
		data->img.img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
		data->img.img_pixels_ptr = mlx_get_data_addr(data->img.img_ptr,
				&data->img.bits_per_pixel, &data->img.line_len, &data->img.endian);
		draw_map(data, data->map);
	}
	return (0);
}

int	loop_hook(t_mlx_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	data->angle_x += 0.05;
	data->angle_y += 0.05;
	data->angle_z += 0.05;
	data->img.img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->img.img_pixels_ptr = mlx_get_data_addr(data->img.img_ptr,
			&data->img.bits_per_pixel, &data->img.line_len, &data->img.endian);
	draw_map(data, data->map);
	return (0);
}

int	main(void)
{
	t_mlx_data	data;
	t_map		*map;

	map = read_map("david.txt");
	if (!map)
	{
		printf("ERROR");
		return (0);
	}
	data.map = map;
	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "FDF PRO");
	data.height = map->height;
	data.width = map->width;
	data.offx = 0;
	data.offy = 0;
	data.angle_x = 0;
	data.angle_y = 0;
	data.angle_z = 0;
	data.is_dragging = 0;
	data.img.img_ptr = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
	data.img.img_pixels_ptr = mlx_get_data_addr(data.img.img_ptr,
			&data.img.bits_per_pixel, &data.img.line_len, &data.img.endian);
	draw_map(&data, map);
	mlx_key_hook(data.win_ptr, handle_input, &data);
	mlx_hook(data.win_ptr, 4, 1L << 2, handle_mouse_press, &data);
	mlx_hook(data.win_ptr, 5, 1L << 3, handle_mouse_release, &data);
	mlx_hook(data.win_ptr, 6, 1L << 6, handle_mouse_move, &data);
	mlx_loop_hook(data.mlx_ptr, loop_hook, &data);
	mlx_loop(data.mlx_ptr);
}
