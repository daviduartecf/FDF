/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:10:41 by daduarte          #+#    #+#             */
/*   Updated: 2024/06/06 17:57:25 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	set_boundries(t_boundries *boundries, t_mlx_data *data, int x, int y)
{
	t_coord	point;
	t_point	point2;

	point2.x = 0;
	point2.y = 0;
	data->boundries_check = 1;
	printf("here %d-----\n", data->map->height);
	while (point2.y < (data->map->height * 20))
	{
		x = 0;
		point2.x = 0;
		if (y >= data->map->height)
			break;
		while (point2.x < (data->map->width[y] * 20))
		{
			if (x >= data->map->width[y])
				break;
			point = project_point(point2.x, point2.y, data->map->map[y][x].z, data);
			if (point.x > data->boundries->max_x)
				data->boundries->max_x = point.x;
			if (point.y > data->boundries->max_y)
				data->boundries->max_y = point.y;
			if (point.x < data->boundries->min_x)
				data->boundries->min_x = point.x;
			if (point.y < data->boundries->min_y)
				data->boundries->min_y = point.y;
			x++;
			point2.x += 20;
		}
		printf("get boundries line %d-----\nof width %d\nx = %d\n------\n", y, data->map->width[y], x);
		y ++;
		point2.y += 20;
	}
	data->boundries_check = 0;
}

void	calculate_boundries(t_mlx_data *data)
{
	int		x;
	int		y;

	data->boundries->min_x = INT_MAX;
	data->boundries->max_x = INT_MIN;
	data->boundries->min_y = INT_MAX;
	data->boundries->max_y = INT_MIN;
	y = 0;
	x = 0;
	printf("GOT BOUNDRIES\n");
	set_boundries(data->boundries, data, x, y);
	printf("GOT BOUNDRIES\n");
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
	else if (keysym == XK_e)
		data->angle_z += 5;
	else if (keysym == XK_q)
		data->angle_z -= 5;
	else if (keysym == XK_r)
		data->rotate = 1;
	else if (keysym == XK_Return)
		data->first_call = 0;
	else if (keysym == XK_Escape)
	{
		printf("Key %d ESQ has been pressed\n\n", keysym);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit(1);
	}
	printf("Key %d has been pressed\n\n", keysym);
	printf("Degree:%f x \n\n", data->angle_x);
	printf("Degree:%f y \n\n", data->angle_y);
	printf("Degree:%f z \n\n", data->angle_z);
	mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	data->img.img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->img.img_pixels_ptr = mlx_get_data_addr(data->img.img_ptr,
			&data->img.bits_per_pixel, &data->img.line_len, &data->img.endian);
	draw_map(data, data->map);
	return (0);
}

int	handle_mouse_press(int button, int x, int y, t_mlx_data *data)
{
	double zoom_factor = 1.05;

	if (button == 1)
	{
		data->is_dragging = 1;
		data->last_x = x;
		data->last_y = y;
	}
	else if (button == MOUSE_SCROLL_UP) {
		// Zoom in
		data->scale *= zoom_factor;
		printf("scale = %f\n", data->scale);
		}
		else if (button == MOUSE_SCROLL_DOWN) {
		// Zoom out
		data->scale /= zoom_factor;
	}
	mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	data->img.img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->img.img_pixels_ptr = mlx_get_data_addr(data->img.img_ptr,
			&data->img.bits_per_pixel, &data->img.line_len, &data->img.endian);
	draw_map(data, data->map);
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
		data->angle_x += dy * 0.1;
		data->angle_y += dx * 0.1;
		data->angle_z += (dx + dy) * 0.1;
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
	if (data->rotate == 1)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
		data->angle_x += 0.05;
		data->angle_y += 0.05;
		data->angle_z += 0.05;
		data->img.img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
		data->img.img_pixels_ptr = mlx_get_data_addr(data->img.img_ptr,
				&data->img.bits_per_pixel, &data->img.line_len, &data->img.endian);
		draw_map(data, data->map);
	}
	return (0);
}

int	close_win(t_mlx_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free(data->mlx_ptr);
	exit(0);
}

void	data_init(t_mlx_data *data, t_map *map)
{
	t_boundries	*boundries;

	data->map = map;
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "FDF PRO");
	data->height = map->height;
	data->width = map->width;
	data->offx = 0;
	data->offy = 0;
	data->angle_x = 45;
	data->angle_y = -35;
	data->angle_z = 30;
	data->is_dragging = 0;
	data->rotate = 0;
	data->first_call = 0;
	data->scale = 1.0;
	data->color1 = 0xFFFFFF;
	data->color2 = 0xFF0000;
	boundries = malloc(sizeof(t_boundries));
	if (!boundries)
		return ;
	boundries->max_x = 0;
	boundries->max_y = 0;
	boundries->min_x = 0;
	boundries->min_y = 0;
	data->boundries = boundries;
}

int	main(int argc, char *argv[])
{

	t_mlx_data	data;
	t_map		*map;

	if (argc == 2)
	{
		printf("string: %s\n", argv[1]);
		map = read_map(argv[1]);
		if (!map)
		{
			printf("No file or no permission!");
			return (0);
		}
		data_init(&data, map);
		data.img.img_ptr = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
		data.img.img_pixels_ptr = mlx_get_data_addr(data.img.img_ptr,
				&data.img.bits_per_pixel, &data.img.line_len, &data.img.endian);
		draw_map(&data, map);
		//draw_isometric_grid(&data, WIDTH, HEIGHT, 50);
		mlx_key_hook(data.win_ptr, handle_input, &data);
		mlx_hook(data.win_ptr, 4, 1L << 2, handle_mouse_press, &data);
		mlx_hook(data.win_ptr, 5, 1L << 3, handle_mouse_release, &data);
		mlx_hook(data.win_ptr, 6, 1L << 6, handle_mouse_move, &data);
		mlx_hook(data.win_ptr, 17, 0L, close_win, &data);
		//mlx_mouse_hook(data.win_ptr, mouse_hook, &data);
		mlx_loop_hook(data.mlx_ptr, loop_hook, &data);
		mlx_loop(data.mlx_ptr);
	}
	else
		printf("Proper usage: ./fdf mapname\n");
}
