/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:14:14 by daduarte          #+#    #+#             */
/*   Updated: 2024/04/29 09:16:23 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/ft_printf.h"

char	*ft_hex_to_char(unsigned long int n);
char	*ft_hex_to_charup(unsigned long n);
int		ft_convert_hex(unsigned long int n, int flag);
int		ft_print_hexup(unsigned int num, int *i);
int		ft_print_hexlow(unsigned int num, int *i);

char	*ft_hex_to_char(unsigned long int n)
{
	unsigned long	temp;
	int				digits;

	temp = n;
	digits = 0;
	auto char base[17] = "0123456789abcdef";
	auto char *s = NULL;
	while (temp != 0)
	{
		digits++;
		temp /= 16;
	}
	s = malloc(sizeof(char) * (digits + 1));
	if (!s)
		return (NULL);
	s[digits] = '\0';
	while (n != 0)
	{
		s[--digits] = base[n % 16];
		n /= 16;
	}
	return (s);
}

char	*ft_hex_to_charup(unsigned long n)
{
	unsigned long	temp;
	int				digits;

	temp = n;
	digits = 0;
	auto char base[17] = "0123456789ABCDEF";
	auto char *s = NULL;
	while (temp != 0)
	{
		digits++;
		temp /= 16;
	}
	s = malloc(sizeof(char) * (digits + 1));
	if (!s)
		return (NULL);
	s[digits] = '\0';
	while (n != 0)
	{
		s[--digits] = base[n % 16];
		n /= 16;
	}
	return (s);
}

int	ft_convert_hex(unsigned long int n, int flag)
{
	int		size;
	char	*s;

	size = 0;
	s = NULL;
	if (n == 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	if (flag == 0)
		s = ft_hex_to_char(n);
	else if (flag == 1)
		s = ft_hex_to_charup(n);
	ft_putstr_fd(s, 1);
	size = ft_strlen(s);
	free(s);
	return (size);
}

int	ft_print_hexlow(unsigned int num, int *i)
{
	int	flag;

	flag = 0;
	*i = *i + 2;
	return (ft_convert_hex((unsigned long)num, flag));
}

int	ft_print_hexup(unsigned int num, int *i)
{
	int	flag;

	flag = 1;
	*i = *i + 2;
	return (ft_convert_hex((unsigned long)num, flag));
}
