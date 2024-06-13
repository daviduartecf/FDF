/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:08:12 by daduarte          #+#    #+#             */
/*   Updated: 2024/04/11 14:21:28 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char *)(s + i) == (unsigned char)c)
			return ((unsigned char *)(s + i));
		i ++;
	}
	return (NULL);
}
/*
#include <stdio.h>
int main()
{
	char *s = "abcde";

	printf("%s", (char *)(ft_memchr(s, 'c', 4)));
}
*/
