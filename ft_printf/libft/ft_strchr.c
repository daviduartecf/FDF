/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:30:37 by daduarte          #+#    #+#             */
/*   Updated: 2024/04/18 15:56:43 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i ++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}
/*
int main()
{
	char *s;
	char *p;

	s = malloc(5);
	s = "olas";
	p = ft_strchr(s, 'a');
	printf("%s", p);
}
*/
