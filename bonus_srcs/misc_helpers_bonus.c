/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_helpers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:47:18 by daduarte          #+#    #+#             */
/*   Updated: 2024/06/13 10:53:28 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	error_management(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf("Proper usage: ./fdf_bonus <mapname>\n");
		exit (0);
	}
	else if (!is_fdf_file(argv[1]))
	{
		ft_printf("File must be in format (.fdf)\n");
		exit (0);
	}
	return (1);
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

int	is_fdf_file(char *s)
{
	int	len;

	len = ft_strlen(s);
	if (s[len - 1] == 'f' && s[len - 2] == 'd'
		&& s[len - 3] == 'f' && s[len - 4] == '.')
		return (1);
	else
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
