/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:16:00 by daduarte          #+#    #+#             */
/*   Updated: 2024/06/06 17:37:41 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	ft_atoi(char *str)
{
	int	i;
	int	neg;
	int	number;

	i = 0;
	neg = 1;
	number = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i ++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i ++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + (str[i] - '0');
		i ++;
	}
	return (number * neg);
}

char	*ft_strdup(char *s)
{
	char	*dup;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
		i ++;
	dup = (char *)malloc((i + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	while (s[j])
	{
		dup[j] = s[j];
		j ++;
	}
	dup[j] = '\0';
	return (dup);
}

int array_len(char **arr)
{
	int len = 0;
	while (arr && arr[len]) {
		len++;
	}
	return len;
}
// Function to join two arrays of strings
char **ft_strarrayjoin(char **arr1, char **arr2)
{
	int len1 = array_len(arr1);
	int len2 = array_len(arr2);
	char **result = malloc((len1 + len2 + 1) * sizeof(char *));
	if (!result) return NULL;
	int i = 0;
	// Copy strings from arr1
	for (int j = 0; j < len1; j++) {
		result[i] = ft_strdup(arr1[j]);
		if (!result[i]) {
			// Free previously allocated strings on failure
			for (int k = 0; k < i; k++) {
				free(result[k]);
			}
			free(result);
			return NULL;
		}
		i++;
	}
	// Copy strings from arr2
	for (int j = 0; j < len2; j++) {
		result[i] = ft_strdup(arr2[j]);
		if (!result[i]) {
			// Free previously allocated strings on failure
			for (int k = 0; k < i; k++) {
				free(result[k]);
			}
			free(result);
			return NULL;
		}
		i++;
	}
	free_array(arr1, len1);
	// Null-terminate the array
	result[i] = NULL;
	return result;
}

int	map_width(char *line, char ***big_str)
{
	int		result;
	int		line_width;
	char	**split_result;

	line_width = 0;
	split_result = ft_split(line, ' ', &line_width);
	if (!split_result)
		return (0);
	//while (split_result[line_width] && split_result[line_width][0] != '\n')
	//	line_width ++;
	*big_str = ft_strarrayjoin(*big_str, split_result);
	if (!big_str)
		return (-1);
	result = line_width;
	while (line_width >= 0)
	{
		free(split_result[line_width]);
		line_width --;
	}
	free(split_result);
	return (result);
}

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
	int	i;

	i = 0;
	if (map)
	{
		while (i < map->height)
		{
			free(map->map[i]);
			i ++;
		}
		free(map->map);
		free(map);
	}
}

t_pt	**atoi_loop(char **strings, int *width, int height, int *color_flag)
{
	int		i;
	int		j;
	int		k;
	t_pt	**map;

	i = 0;
	j = 0;
	k = 0;
	map = allocate_map(width, height);
	while (i < height)
	{
		k = 0;
		while (k < width[i] && strings[j])
		{
			get_altitude_and_color(strings[j], &map[i][k], color_flag);
			//printf("ATOI line %d ---\n", k);
			k ++;
			j ++;
		}
		i ++;
	}
	return (map);
}
