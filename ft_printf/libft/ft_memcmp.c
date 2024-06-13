/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:46:27 by daduarte          #+#    #+#             */
/*   Updated: 2024/04/15 12:05:56 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char *)(s1 + i) != *(unsigned char *)(s2 + i))
		{
			return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
		}
		i ++;
	}
	return (0);
}
// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	char *s1 = "abcdef";
// 	char *s2 = "fgd";
// 	int i = 0;

// 	i = ft_memcmp(s1, s2, 8);
// 	printf("%d\n", i);
// 	i = memcmp(s1, s2, 3);
// 	printf("%d", i);
// }
