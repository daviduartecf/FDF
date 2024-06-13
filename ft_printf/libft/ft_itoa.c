/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:08:23 by daduarte          #+#    #+#             */
/*   Updated: 2024/04/18 12:12:03 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	int_len(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i = 1;
	while (n != 0)
	{
		i ++;
		n = n / 10;
	}
	return (i);
}

static	char	*malloc_it(char *result, int size, int n)
{
	result = malloc((size + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	if (n < 0)
		result[0] = '-';
	else if (n == 0)
		result[0] = '0';
	return (result);
	return (result);
}

static	char	*create_str(char *res, int n, int size)
{
	while (n > 0)
	{
		res[--size] = (n % 10) + '0';
		n = n / 10;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*result;

	if (n == -2147483648)
	{
		result = ft_strdup("-2147483648");
		return (result);
	}
	len = int_len(n);
	result = NULL;
	result = malloc_it(result, len, n);
	if (!result)
		return (NULL);
	if (n < 0)
		n = -n;
	result = create_str(result, n, len);
	result[len] = '\0';
	return (result);
}
