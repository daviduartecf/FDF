/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:10:41 by daduarte          #+#    #+#             */
/*   Updated: 2024/06/13 11:21:18 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	close_win(t_mlx_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free_map(data->map);
	free(data->mlx_ptr);
	free(data->boundaries);
	exit(1);
	return (0);
}

void	image_destroy_and_create(t_mlx_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	data->img.img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->img.img_pixels_ptr = mlx_get_data_addr(data->img.img_ptr,
			&data->img.bits_per_pixel, &data->img.line_len, &data->img.endian);
}

void	hooks_call(t_mlx_data *data)
{
	mlx_key_hook(data->win_ptr, handle_input, data);
	mlx_hook(data->win_ptr, 4, 1L << 2, handle_mouse_press, data);
	mlx_hook(data->win_ptr, 5, 1L << 3, handle_mouse_release, data);
	mlx_hook(data->win_ptr, 6, 1L << 6, handle_mouse_move, data);
	mlx_hook(data->win_ptr, 17, 0L, close_win, data);
	mlx_loop_hook(data->mlx_ptr, loop_hook, data);
	mlx_loop(data->mlx_ptr);
}

int	main(int argc, char *argv[])
{
	t_mlx_data	data;
	t_map		*map;

	if (error_management(argc, argv))
	{
		map = read_map(argv[1]);
		if (!map)
		{
			ft_printf("Error opening file.");
			return (0);
		}
		data_init(&data, map);
		if (data.first_call == 0)
		{
			draw_map(&data, map);
			image_destroy_and_create(&data);
		}
		draw_map(&data, map);
		hooks_call(&data);
	}
	else
		ft_printf("Proper usage: ./fdf <mapname>\n");
	return (0);
}
