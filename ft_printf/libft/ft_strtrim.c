/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:55:51 by daduarte          #+#    #+#             */
/*   Updated: 2024/04/16 15:03:16 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	check_char(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i ++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		start;
	int		end;
	int		size;
	char	*str;

	i = 0;
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && check_char(s1[start], set))
		start ++;
	while (start < end && check_char(s1[end], set))
		end --;
	size = end - start + 1;
	str = malloc((size + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < size)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}
// #include <stdio.h>
// int main()
// {
// 	printf("%s\n", ft_strtrim("aaaaabbxxxxxzab", "azb"));
// }
