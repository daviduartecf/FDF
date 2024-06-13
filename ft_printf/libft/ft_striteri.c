/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:32:53 by daduarte          #+#    #+#             */
/*   Updated: 2024/04/18 15:40:12 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (i < ft_strlen(s))
	{
		f(i, &s[i]);
		i ++;
	}
}
// #include <stdio.h>
// int main()
// {
// 	char str[] = "hello";

// 	printf("Before: %s\n", str);
//     ft_striteri(str, function);
//     printf("After: %s\n", str);

// }
// void	function(unsigned int x, char *s)
// {
// 	s[0] = 'b';
// }
