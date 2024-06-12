/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:39:20 by daduarte          #+#    #+#             */
/*   Updated: 2024/06/12 14:46:57 by daduarte         ###   ########.fr       */
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
