/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 11:31:41 by daduarte          #+#    #+#             */
/*   Updated: 2024/05/08 11:31:42 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen(char *s);
int		ft_strchr(char *s);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_calloc(size_t nmemb, size_t size);

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*array;
	size_t	i;

	array = (void *)malloc(nmemb * size);
	if (!array)
		return (NULL);
	i = 0;
	while (i < (nmemb * size))
	{
		*(unsigned char *)(array + i) = 0;
		i ++;
	}
	return ((char *)array);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		s1len;
	int		s2len;
	int		i;

	if (!s2)
		return (NULL);
	s1len = 0;
	s2len = ft_strlen(s2);
	i = -1;
	while (s1[s1len])
		s1len ++;
	str = malloc((s1len * sizeof(char)) + (s2len * sizeof(char)) + 1);
	if (!str)
		return (NULL);
	while (++i < s1len)
		str[i] = s1[i];
	i = 0;
	while (i < s2len)
		str[s1len++] = s2[i++];
	str[s1len] = '\0';
	free(s1);
	return (str);
}

int	ft_strchr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i ++;
	}
	return (0);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i ++;
	return (i);
}
