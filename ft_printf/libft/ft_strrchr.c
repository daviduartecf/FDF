/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:52:38 by daduarte          #+#    #+#             */
/*   Updated: 2024/04/18 15:56:36 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i ++;
	while (i >= 0)
	{
		if (s[i] == (char)c)
		{
			return ((char *)(s + i));
		}
		i --;
	}
	return (NULL);
}
/*
#include <stdio.h>
int main()
{
	char *s;
	char *p;
	size_t x;

	s = malloc(5);
	s = "olas";
	p = ft_strrchr(s, 'a');
	printf("%s", p);
}
*/
