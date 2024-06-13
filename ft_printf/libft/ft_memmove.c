/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:25:56 by daduarte          #+#    #+#             */
/*   Updated: 2024/04/17 17:02:42 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int	i;

	if (dest == NULL && src == NULL)
		return (NULL);
	if (dest > src)
	{
		i = (int)n - 1;
		while (i >= 0)
		{
			*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
			i --;
		}
	}
	else
	{
		i = 0;
		while (i < (int)n)
		{
			*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
			i++;
		}
	}
	return (dest);
}
// #include <stdio.h>
// int	main()
// {
// 	char string1[15] = "abcde";
// 	char *string2 = malloc(15 * sizeof(char));

// 	printf("%s \n", string2);
// 	ft_memmove(string2, string1, 3);
// 	printf("%s \n", string2);
// 	ft_memmove(string2, "concon", 3);
// 	printf("%s \n", string2);
// }
