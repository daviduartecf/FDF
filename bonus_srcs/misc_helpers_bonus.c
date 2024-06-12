/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_helpers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:47:18 by daduarte          #+#    #+#             */
/*   Updated: 2024/06/12 16:24:05 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

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

void	*return_null(t_map *map, char **big_str, int flag)
{
	if (flag == 1)
	{
		free(map);
		free_array(big_str, array_len(big_str));
		return (NULL);
	}
	else if (flag == 2)
	{
		free(map->width);
		free(map);
		return (NULL);
	}
	else if (flag == 3)
	{
		free_array(big_str, array_len(big_str));
		return (NULL);
	}
	else if (flag == 4)
	{
		free(big_str);
		return (NULL);
	}
	return (NULL);
}

int	handle_z_factor(int keysym, t_mlx_data *data)
{
	if (keysym == XK_KP_Add)
	{
		if (data->z_factor + 1 <= 10)
			data->z_factor += 1;
		else
			return (0);
	}
	if (keysym == XK_KP_Subtract)
	{
		if (data->z_factor - 1 > 0)
			data->z_factor -= 1;
		else
			return (0);
	}
	return (0);
}

int	calculate_offset(t_mlx_data *data, int flag)
{
	int	offset;

	offset = 0;
	if (flag == 1)
		offset = (WIDTH - (data->boundaries->max_x - data->boundaries->min_x))
			/ 2 - data->boundaries->min_x + data->translate_x;
	else if (flag == 2)
		offset = (HEIGHT - (data->boundaries->max_y - data->boundaries->min_y))
			/ 2 - data->boundaries->min_y + data->translate_y;
	return (offset);
}
