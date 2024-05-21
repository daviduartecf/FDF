/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:53:54 by daduarte          #+#    #+#             */
/*   Updated: 2024/05/21 11:29:21 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	int	count_strs(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			i ++;
		else
		{
			count ++;
			while (s[i] != c && s[i])
				i ++;
		}
	}
	return (count);
}

static	int	count_chars(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != c && s[i])
	{
		count ++;
		i ++;
	}
	return (count);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i ++;
		}
		dst[i] = '\0';
	}
	while (src[i])
		i ++;
	return (i);
}

static	char	*populate_array(char const *s, char c, int *i)
{
	int		str_len;
	char	*array;

	str_len = count_chars(s, c);
	array = malloc((str_len + 1) * sizeof(char));
	if (!array)
		return (NULL);
	ft_strlcpy(array, s, (str_len + 1));
	*i = *i + str_len;
	return (array);
}

static	void	free_array(char **array, int k)
{
	while (k >= 0)
	{
		free(array[k]);
		k --;
	}
	free(array);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		k;
	int		size;
	char	**array;

	i = 0;
	k = 0;
	size = count_strs(s, c);
	array = malloc((size + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	while (k < size)
	{
		while (s[i] == c)
			i++;
		array[k] = populate_array(&s[i], c, &i);
		if (array[k] == NULL)
		{
			free_array(array, k);
			return (NULL);
		}
		k ++;
	}
	array[size] = 0;
	return (array);
}
