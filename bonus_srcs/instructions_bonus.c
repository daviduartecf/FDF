/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:14:15 by daduarte          #+#    #+#             */
/*   Updated: 2024/06/13 11:15:10 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	call_instructions(t_mlx_data *data)
{
	if (data->show_help == 1)
		display_instructions(data);
	if (data->show_help == 0)
		mlx_string_put(data->mlx_ptr, data->win_ptr, 15, 20,
			0xFFFFFF, "Press 'H' for help");
}

void	rotate_instructions(t_mlx_data *data, int *y)
{
	*y += 15;
	mlx_string_put(data->mlx_ptr, data->win_ptr, 18, *y,
		0xFFFFFF, "W/S -> Rotate X axis");
	*y += 15;
	mlx_string_put(data->mlx_ptr, data->win_ptr, 18, *y,
		0xFFFFFF, "A/D -> Rotate Y axis");
	*y += 15;
	mlx_string_put(data->mlx_ptr, data->win_ptr, 18, *y,
		0xFFFFFF, "Q/E -> Rotate Z axis");
}

void	translate_instructions(t_mlx_data *data, int *y)
{
	*y += 15;
	mlx_string_put(data->mlx_ptr, data->win_ptr, 18, *y,
		0xFFFFFF, "Up/Down -> Translate Y");
	*y += 15;
	mlx_string_put(data->mlx_ptr, data->win_ptr, 18, *y,
		0xFFFFFF, "Left/Right -> Translate X");
}

void	zoom_scale_instructions(t_mlx_data *data, int *y)
{
	*y += 15;
	mlx_string_put(data->mlx_ptr, data->win_ptr, 18, *y,
		0xFFFFFF, "Wheel Up -> Zoom in");
	*y += 15;
	mlx_string_put(data->mlx_ptr, data->win_ptr, 18, *y,
		0xFFFFFF, "Wheel Down -> Zoom out");
	*y += 15;
	mlx_string_put(data->mlx_ptr, data->win_ptr, 18, *y,
		0xFFFFFF, "-/+ -> Change altitude scale");
}

void	display_instructions(t_mlx_data *data)
{
	int	y;

	y = 40;
	mlx_string_put(data->mlx_ptr, data->win_ptr, 15, 20,
		0xFFFFFF, "Press 'H' to hide help");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 18, y,
		0xFFFFFF, "Instructions:");
	y += 15;
	mlx_string_put(data->mlx_ptr, data->win_ptr, 18, y,
		0xFFFFFF, "R -> Toggle rotate");
	y += 15;
	mlx_string_put(data->mlx_ptr, data->win_ptr, 18, y,
		0xFFFFFF, "C -> Change color");
	y += 15;
	mlx_string_put(data->mlx_ptr, data->win_ptr, 18, y,
		0xFFFFFF, "P -> Parallel projection");
	y += 15;
	mlx_string_put(data->mlx_ptr, data->win_ptr, 18, y,
		0xFFFFFF, "I -> Isometric projection");
	rotate_instructions(data, &y);
	translate_instructions(data, &y);
	zoom_scale_instructions(data, &y);
	y += 15;
	mlx_string_put(data->mlx_ptr, data->win_ptr, 18, y,
		0xFFFFFF, "Esc -> Exit");
}
