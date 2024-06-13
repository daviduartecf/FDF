/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:05:01 by daduarte          #+#    #+#             */
/*   Updated: 2024/04/16 09:35:27 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && (s1[i] || s2[i]))
	{
		if (((unsigned char)s1[i] != (unsigned char)s2[i]))
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i ++;
	}
	return (0);
}
// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	char *s1 = "1235";
// 	char *s2 = "1234";
// 	int i = 0;

// 	i = ft_strncmp(s1, s2, 5);
// 	printf("%d\n", i);
// 	i = strncmp(s1, s2, 5);
// 	printf("%d", i);
// }
