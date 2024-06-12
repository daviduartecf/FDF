/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:47:18 by daduarte          #+#    #+#             */
/*   Updated: 2024/06/12 11:48:38 by daduarte         ###   ########.fr       */
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
	else if (keysym == XK_r)
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
