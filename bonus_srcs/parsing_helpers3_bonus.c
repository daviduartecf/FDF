/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:38:28 by daduarte          #+#    #+#             */
/*   Updated: 2024/06/12 10:28:01 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	get_max_value(int *width, int height)
{
	int	i;
	int	max;

	i = 0;
	max = INT_MIN;
	while (i < height)
	{
		if (width[i] > max)
			max = width[i];
		i ++;
	}
	return (max);
}

void	free_map(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	if (map)
	{
		while (y < map->height)
		{
			free(map->map[y]);
			y ++;
		}
		free(map->map);
		free(map->width);
		free(map);
	}
}

int	array_len(char **arr)
{
	int	len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}

void	ft_copy_array(char **result, char **arr1, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		result[i] = ft_strdup(arr1[i]);
		if (!(result[i]))
		{
			free_array(result, i);
			return ;
		}
		i++;
	}
}

void	initialize_array(int *array, int size)
{
	int	i;

	i = 0;
	while (i < size)
		array[i++] = 0;
}
