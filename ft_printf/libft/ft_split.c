/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:53:54 by daduarte          #+#    #+#             */
/*   Updated: 2024/04/24 10:13:37 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
// #include <stdio.h>
// int main()
// {
// 	int	i;
// 	char	**array;

// 	i = 0;
// 	array = ft_split("acabou,, sad,asd", ',');
// 	while (array[i])
// 	{
// 		printf("%s\n", array[i++]);
// 	}
// 	printf("%d", i);
// 	free_array(array, (i));
// }
