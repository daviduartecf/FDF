/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_functions_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:39:20 by daduarte          #+#    #+#             */
/*   Updated: 2024/06/13 11:03:08 by daduarte         ###   ########.fr       */
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
		|| keysym == XK_Right || keysym == XK_k || keysym == XK_o)
		handle_translate(keysym, data);
	else if (keysym == XK_KP_Add || keysym == XK_KP_Subtract)
		handle_z_factor(keysym, data);
	else if (keysym == XK_p || keysym == XK_i || keysym == XK_c)
		projections(keysym, data);
	else if ((keysym == XK_h || keysym == XK_H))
	{
		if (data->show_help == 1)
			data->show_help = 0;
		else
			data->show_help = 1;
		display_instructions(data);
	}
	else if (keysym == XK_Escape)
		close_win(data);
	image_destroy_and_create(data);
	draw_map(data, data->map);
	return (0);
}

int	handle_mouse_press(int button, int x, int y, t_mlx_data *data)
{
	static double	max_up;
	static double	max_down;

	if (data->no_scale == 0)
	{
		max_up = data->scale * 35;
		max_down = data->scale / 25;
		data->no_scale = 2;
	}
	if (button == 1)
	{
		data->is_dragging = 1;
		data->last_x = x;
		data->last_y = y;
	}
	else if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
		zoom_up_down(data, max_up, max_down, button);
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
