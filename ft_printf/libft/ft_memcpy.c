/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:49:31 by daduarte          #+#    #+#             */
/*   Updated: 2024/04/19 10:20:05 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
		i ++;
	}
	return (dest);
}
// #include <stdio.h>
// int	main()
// {
// 	char string1[5] = "abcd";
// 	char *string2;

// 	string2 = malloc((3 + 1) * sizeof(char));
// 	printf("%s \n", string2);
// 	ft_memcpy(string2, string1, 3);
// 	printf("%s \n", string2);
// }
