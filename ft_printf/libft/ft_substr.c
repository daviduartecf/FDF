/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:29:45 by daduarte          #+#    #+#             */
/*   Updated: 2024/04/18 13:05:42 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start,
size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*str;

	i = 0;
	s_len = 0;
	s_len = ft_strlen(s);
	if (len > s_len - start)
		len = s_len - start;
	if (start >= (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start];
		i ++;
		start ++;
	}
	str[i] = '\0';
	return (str);
}
// #include <stdio.h>
// int main()
// {
// 	char *s;

// 	s = ft_substr("abcde", 2, 8);
// 	//s = ft_substr("hola", 4294967295, 0);
// 	printf("%s\n", s);
// 	free(s);
// }
