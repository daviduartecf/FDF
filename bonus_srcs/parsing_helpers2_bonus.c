/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:13:53 by daduarte          #+#    #+#             */
/*   Updated: 2024/06/12 14:00:53 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/* char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i ++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
} */

int	get_digit(char c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return (10 + c - 'a');
	else
		return (-1);
}

int	ft_atoibase_fdf(char *str)
{
	int	i;
	int	result;

	i = 1;
	result = 0;
	while (get_digit(str[i]) >= 0 && str[i])
	{
		result = result * 16;
		result = result + get_digit(str[i]);
		i ++;
	}
	return (result);
}

void	get_altitude_and_color(char *str, t_pt *point, int *color_flag)
{
	char	*color;

	color = ft_strchr(str, 'x');
	point->z = ft_atoi(str);
	if (color)
	{
		point->color = ft_atoibase_fdf(color);
		*color_flag = 1;
	}
	else
		point->color = 0xFFFFFF;
}

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}
