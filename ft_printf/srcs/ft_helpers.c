/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:42:19 by daduarte          #+#    #+#             */
/*   Updated: 2024/04/25 15:13:30 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/ft_printf.h"

int		ft_int_len(int n);
int		ft_ptr_len(long n);
int		ft_uint_len(unsigned int n);
int		ft_check_char(char c, const char *set);
void	ft_putuint_fd(unsigned int n, int fd);

int	ft_int_len(int n)
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

int	ft_uint_len(unsigned int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i = 1;
	while (n > 0)
	{
		i ++;
		n = n / 10;
	}
	return (i);
}

int	ft_ptr_len(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		i = 1;
	while (n > 0)
	{
		i ++;
		n = n / 16;
	}
	return (i);
}

int	ft_check_char(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i ++;
	}
	return (0);
}

void	ft_putuint_fd(unsigned int n, int fd)
{
	if (n >= 10)
	{
		ft_putnbr_fd((n / 10), fd);
		ft_putchar_fd(((n % 10) + '0'), fd);
	}
	else
		ft_putchar_fd(((n % 10) + '0'), fd);
}
