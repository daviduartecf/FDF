/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:39:20 by daduarte          #+#    #+#             */
/*   Updated: 2024/06/13 10:54:28 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	handle_input(int keysym, t_mlx_data *data)
{
	if (keysym == XK_Escape)
		close_win(data);
	image_destroy_and_create(data);
	draw_map(data, data->map);
	return (0);
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
	else if (keysym == XK_l)
	{
		data->translate_x -= 5;
		data->translate_y += 5;
	}
	else if (keysym == XK_p)
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
