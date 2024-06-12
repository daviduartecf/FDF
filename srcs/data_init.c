/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:51:53 by daduarte          #+#    #+#             */
/*   Updated: 2024/06/12 11:42:06 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	map_init(t_map *map, int height, int *width)
{
	int	i;

	i = 0;
	map->color_flag = 0;
	map->height = height;
	map->width = malloc(height * sizeof(int));
	if (!map->width)
		return ;
	while (i < height)
	{
		map->width[i] = width[i];
		i ++;
	}
}

void	boundaries_init(t_mlx_data *data)
{
	t_boundaries	*boundaries;

	boundaries = malloc(sizeof(t_boundaries));
	if (!boundaries)
		return ;
	boundaries->max_x = 0;
	boundaries->max_y = 0;
	boundaries->min_x = 0;
	boundaries->min_y = 0;
	data->boundaries = boundaries;
}

void	data_init(t_mlx_data *data, t_map *map)
{
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
	data->no_scale = 1;
	data->scale = 1.0;
	data->color1 = 0xFFFFFF;
	data->color2 = 0xFF0000;
	data->translate_x = 0;
	data->translate_y = 0;
	data->img.img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->img.img_pixels_ptr = mlx_get_data_addr(data->img.img_ptr,
			&data->img.bits_per_pixel, &data->img.line_len, &data->img.endian);
	boundaries_init(data);
}
