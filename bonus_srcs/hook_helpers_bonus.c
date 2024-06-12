/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:13:47 by daduarte          #+#    #+#             */
/*   Updated: 2024/06/12 17:18:43 by daduarte         ###   ########.fr       */
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
