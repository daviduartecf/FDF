/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:39:20 by daduarte          #+#    #+#             */
/*   Updated: 2024/06/12 11:39:53 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	handle_input(int keysym, t_mlx_data *data)
{
	if (keysym == XK_w || keysym == XK_s || keysym == XK_d
		|| keysym == XK_a || keysym == XK_e || keysym == XK_q
		|| keysym == XK_r)
		handle_rotate(keysym, data);
	else if (keysym == XK_Up || keysym == XK_Down || keysym == XK_Left
		|| keysym == XK_Right || keysym == XK_p || keysym == XK_l)
		handle_translate(keysym, data);
	else if (keysym == XK_Escape)
		close_win(data);
	image_destroy_and_create(data);
	draw_map(data, data->map);
	return (0);
}

int	handle_mouse_press(int button, int x, int y, t_mlx_data *data)
{
	double	zoom_factor;

	zoom_factor = 1.05;
	if (button == 1)
	{
		data->is_dragging = 1;
		data->last_x = x;
		data->last_y = y;
	}
	else if (button == MOUSE_SCROLL_UP)
		data->scale *= zoom_factor;
	else if (button == MOUSE_SCROLL_DOWN)
		data->scale /= zoom_factor;
	image_destroy_and_create(data);
	draw_map(data, data->map);
	return (0);
}

int	handle_mouse_release(int button, int x, int y, t_mlx_data *data)
{
	if (button == 1)
		data->is_dragging = 0;
	x = x + 0;
	y = y + 0;
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
		image_destroy_and_create(data);
		draw_map(data, data->map);
	}
	return (0);
}

int	loop_hook(t_mlx_data *data)
{
	if (data->rotate == 1)
	{
		data->angle_x += 0.05;
		data->angle_y += 0.05;
		data->angle_z += 0.05;
		image_destroy_and_create(data);
		draw_map(data, data->map);
	}
	return (0);
}
