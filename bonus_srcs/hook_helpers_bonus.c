/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_helpers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:13:47 by daduarte          #+#    #+#             */
/*   Updated: 2024/06/13 11:13:48 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	zoom_up_down(t_mlx_data *data, double max, double min, int button)
{
	if (button == MOUSE_SCROLL_UP)
	{
		if (data->scale * ZOOM_FACTOR > max)
			return (0);
		data->scale *= ZOOM_FACTOR;
	}
	else if (button == MOUSE_SCROLL_DOWN)
	{
		if (data->scale / ZOOM_FACTOR < min)
			return (0);
		data->scale /= ZOOM_FACTOR;
	}
	return (1);
}

void	change_color(t_mlx_data *data)
{
	if (data->color1 == 0xFFFFFF)
	{
		data->color1 = 0x0000FF;
		data->color2 = 0xFF0000;
	}
	else if (data->color1 == 0x0000FF)
	{
		data->color1 = 0xFFFF00;
		data->color2 = 0xFF0000;
	}
	else if (data->color1 == 0xFFFF00)
	{
		data->color1 = 0xFFFFFF;
		data->color2 = 0xFF0000;
	}
}

void	projections(int keysym, t_mlx_data *data)
{
	if (keysym == XK_p)
	{
		data->angle_x = 90;
		data->angle_y = 0;
		data->angle_z = 0;
	}
	else if (keysym == XK_i)
	{
		data->angle_x = 45;
		data->angle_y = -35;
		data->angle_z = 30;
	}
	else if (keysym == XK_c)
	{
		change_color(data);
	}
}

void	handle_translate(int keysym, t_mlx_data *data)
{
	if (keysym == XK_Up)
		data->translate_y -= 5;
	else if (keysym == XK_Down)
		data->translate_y += 5;
	else if (keysym == XK_Right)
		data->translate_x += 5;
	else if (keysym == XK_Left)
		data->translate_x -= 5;
	else if (keysym == XK_k)
	{
		data->translate_x -= 5;
		data->translate_y += 5;
	}
	else if (keysym == XK_o)
	{
		data->translate_x += 5;
		data->translate_y -= 5;
	}
}

void	handle_rotate(int keysym, t_mlx_data *data)
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
	else if (data->rotate == 1 && keysym == XK_r)
	{
		data->rotate = 0;
		return ;
	}
	else if (data->rotate == 0 && keysym == XK_r)
		data->rotate = 1;
}
