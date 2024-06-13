/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:01:06 by daduarte          #+#    #+#             */
/*   Updated: 2024/04/19 09:30:23 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		s1len;
	int		s2len;
	int		i;

	s1len = 0;
	s2len = 0;
	i = 0;
	while (s1[s1len])
		s1len ++;
	while (s2[s2len])
		s2len ++;
	str = malloc((s1len * sizeof(char)) + (s2len * sizeof(char)) + 1);
	if (!str)
		return (NULL);
	while (i < s1len)
	{
		str[i] = s1[i];
		i ++;
	}
	i = 0;
	while (i < s2len)
		str[s1len++] = s2[i++];
	str[s1len] = '\0';
	return (str);
}
//#include <stdio.h>
// int	main(int argc, char *argv[])
// {
// 	char *s1 = argv[1];
// 	char *s2 = argv[2];
// 	if (argc > 1)
// 	{
// 		printf("ok\n");
// 	}
// 	printf("%s\n", ft_strjoin(s1, s2));
// }
// int		main()
// {
// 	char	s1[] = "lorem ipsum";
// 	char	s2[] = "dolor sit amet";
// 	char	*strjoin;

// 	if (!(strjoin = ft_strjoin(s1, s2)))
// 		printf("NULL");
// 	else
// 		printf("%s\n", strjoin);
// 	if (strjoin == s1 || strjoin == s2)
// 		printf("\nA new string was not returned");
// }
