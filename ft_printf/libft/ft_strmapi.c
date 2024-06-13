/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:10:53 by daduarte          #+#    #+#             */
/*   Updated: 2024/04/18 15:41:17 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		size;
	char	*result;

	i = 0;
	size = ft_strlen(s);
	result = malloc((size + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (s[i])
	{
		result[i] = f(i, s[i]);
		i ++;
	}
	result[i] = '\0';
	return (result);
}
// #include <stdio.h>
// int	main()
// {
// 	char *s;

// 	s = ft_strmapi("aaannjhaa", function);
// 	printf("%s", s);
// }
// char	function(unsigned int x, char c)
// {
// 	if (x >= 0)
// 		c = 'b';
// 	return (c);
// }
