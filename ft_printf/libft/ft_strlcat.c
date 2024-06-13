/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:13:20 by daduarte          #+#    #+#             */
/*   Updated: 2024/04/19 09:28:30 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	dstlen;

	srclen = 0;
	dstlen = 0;
	while (dst[dstlen])
		dstlen++;
	if (dstlen < size)
	{
		while (src[srclen] && (dstlen < size - 1 - srclen))
		{
			dst[dstlen + srclen] = src[srclen];
			srclen++;
		}
		dst[dstlen + srclen] = '\0';
	}
	while (src[srclen])
		srclen++;
	if (dstlen >= size)
		dstlen = size;
	return (dstlen + srclen);
}
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// int main()
// {
// 	char s1[7] = " Mundo";
// 	//char *s2;
// 	char s2[] = "OLA";
// 	int i;

// 	//i = ft_strlcat(s2, s1, 1);
// 	//i = ft_strlcat(s2, s1, 3);
// 	//s2 = (char *)malloc(sizeof(*s2) * 15);
// 	printf("BEFOR FUNC %s\n", s2);
// 	i = ft_strlcat(s2, s1, 20);
// 	printf("AFTER FUNC %s\n", s2);
// 	//memset(s2, 'r', 15);
// 	//i = ft_strlcat(s2, "lorem ipsum dolor sit amet", 10);
// 	printf("Final size: %d\n", i);
// }
