/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:41:21 by daduarte          #+#    #+#             */
/*   Updated: 2024/04/11 14:23:35 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
/*
#include <stdio.h>
#include <stdlib.h>
int main()
{
	const char s1[6] = "abcde";
	//char s1[1] = "";
	char s2[6] = "zezed";
	int i;

	//s2 = malloc(6);
	//s2 = "zeeds";
	i = ft_strlcpy(s2, s1, 1);
	//i = ft_strlcpy(s2, s1, 3);
	//i = ft_strlcpy(s2, s1, 7);
	printf("%s\n", s2);
	printf("%d", i);
	//free(s2);
}
*/
