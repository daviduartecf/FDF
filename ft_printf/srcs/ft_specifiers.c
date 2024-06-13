/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifiers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:00:16 by daduarte          #+#    #+#             */
/*   Updated: 2024/04/29 09:20:30 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/ft_printf.h"

int	ft_print_str(char *s, int *i);
int	ft_print_int(va_list args, int *i);
int	ft_print_char(va_list args, int *i);
int	ft_print_uint(va_list args, int *i);
int	ft_print_pointer(va_list args, int *i);

int	ft_print_str(char *s, int *i)
{
	if (s == NULL)
	{
		ft_putstr_fd("(null)", 1);
		*i = *i + 2;
		return (ft_strlen("(null)"));
	}
	ft_putstr_fd(s, 1);
	*i = *i + 2;
	return (ft_strlen(s));
}

int	ft_print_int(va_list args, int *i)
{
	int	num;

	num = va_arg(args, int);
	ft_putnbr_fd(num, 1);
	num = ft_int_len(num);
	*i = *i + 2;
	return (num);
}

int	ft_print_char(va_list args, int *i)
{
	char	c;

	c = (char)va_arg(args, int);
	ft_putchar_fd(c, 1);
	*i = *i + 2;
	return (1);
}

int	ft_print_pointer(va_list args, int *i)
{
	void	*p;
	int		size;
	int		flag;

	flag = 0;
	p = va_arg(args, void *);
	if (p == NULL)
	{
		ft_putstr_fd("(nil)", 1);
		*i = *i + 2;
		return (ft_strlen("(nil)"));
	}
	ft_putstr_fd("0x", 1);
	*i = *i + 2;
	size = ft_convert_hex((unsigned long)p, flag) + 2;
	return (size);
}

int	ft_print_uint(va_list args, int *i)
{
	unsigned int	num;

	num = va_arg(args, unsigned int);
	ft_putuint_fd(num, 1);
	*i = *i + 2;
	return (ft_uint_len(num));
}
