/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 09:31:34 by daduarte          #+#    #+#             */
/*   Updated: 2024/04/17 16:31:18 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = 0;
		i ++;
	}
}
// #include <strings.h>
// #include <stdio.h>
// int	main(void)
// {
// 	char	s[] = "";
// 	int	i;

// 	i = 0;
// 	bzero(s, 3);
// 	printf("NADA");
// 	while (s[i] != '\0')
// 	{
// 		printf("%c", s[i++]);
// 	}
// 	printf("\n");
// 	i = 0;
// 	ft_bzero(s, 2);
// 	while (i < 4)
// 	{
// 		printf("%c", s[i++]);
// 	}
// }
