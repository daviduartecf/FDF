/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:38:09 by daduarte          #+#    #+#             */
/*   Updated: 2024/04/29 09:18:06 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/ft_printf.h"

int		ft_process_specifier(va_list args, const char *str, int size);
void	ft_conversions(va_list args, char c, int *i, int *total);

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		print_count;
	int		size;

	print_count = 0;
	size = ft_strlen(str);
	va_start(args, str);
	print_count = ft_process_specifier(args, str, size);
	va_end(args);
	return (print_count);
}

int	ft_process_specifier(va_list args, const char *str, int size)
{
	char	*specifiers;
	int		i;
	int		total;

	specifiers = "cspdiuxX%";
	i = 0;
	total = 0;
	while (i < size && str[i] != '\0')
	{
		if (str[i] == FORMAT_CHAR && ft_check_char(str[i + 1], specifiers))
		{
			ft_conversions(args, str[i + 1], &i, &total);
			total = total - 2;
		}
		else if (str[i])
			ft_putchar_fd(str[i++], 1);
	}
	total += i;
	return (total);
}

void	ft_conversions(va_list args, char c, int *i, int *total)
{
	if (c == STR)
		*total += ft_print_str(va_arg(args, char *), i);
	else if (c == POINT)
		*total += ft_print_pointer(args, i);
	else if (c == CHAR)
		*total += ft_print_char(args, i);
	else if (c == HEXLOWER)
		*total += ft_print_hexlow(va_arg(args, unsigned int), i);
	else if (c == HEXUPPER)
		*total += ft_print_hexup(va_arg(args, unsigned int), i);
	else if (c == INT || c == DEC)
		*total += ft_print_int(args, i);
	else if (c == UNSIG_DEC)
		*total += ft_print_uint(args, i);
	else if (c == FORMAT_CHAR)
	{
		ft_putchar_fd('%', 1);
		*i = *i + 2;
		*total += 1;
	}
}
