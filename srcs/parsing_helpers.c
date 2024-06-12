/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:16:00 by daduarte          #+#    #+#             */
/*   Updated: 2024/06/12 09:50:55 by daduarte         ###   ########.fr       */
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
	if (!s)
		return (NULL);
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

char	**ft_strarrayjoin(char **arr1, char **arr2)
{
	int		i;
	int		len1;
	int		len2;
	char	**result;

	len1 = array_len(arr1);
	len2 = array_len(arr2);
	result = calloc((len1 + len2 + 1), sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	ft_copy_array(result, arr1, len1);
	while (i < len2)
	{
		result[len1 + i] = ft_strdup(arr2[i]);
		if (!result[len1 + i])
		{
			free_array(result, len1 + i);
			return (NULL);
		}
		i ++;
	}
	result[len1 + len2] = NULL;
	free_array(arr1, (len1));
	return (result);
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
			k ++;
			j ++;
		}
		i ++;
	}
	return (map);
}
