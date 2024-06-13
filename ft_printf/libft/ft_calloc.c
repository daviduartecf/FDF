/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:21:03 by daduarte          #+#    #+#             */
/*   Updated: 2024/04/18 16:23:52 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*array;

	if (nmemb * size >= 184467440737095516)
		return (NULL);
	array = (void *)malloc(nmemb * size);
	if (!array)
		return (NULL);
	ft_bzero(array, (nmemb * size));
	return (array);
}
// #include <stdio.h>
// int main()
// {
// 	char *s1;
// 	size_t	i = 0;
// 	size_t size = 3;

// 	s1 = ft_calloc(size, 1);
// 	while (i < size)
// 	{
// 		printf("%d\n", s1[i]);
// 		i ++;
// 	}
// 	free(s1);
// }
