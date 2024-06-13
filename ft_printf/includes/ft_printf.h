/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:07:48 by daduarte          #+#    #+#             */
/*   Updated: 2024/04/29 09:18:28 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <limits.h>

# define FORMAT_CHAR '%'
# define DEC 'd'
# define INT 'i'
# define CHAR 'c'
# define STR 's'
# define POINT 'p'
# define UNSIG_DEC 'u'
# define HEXLOWER 'x'
# define HEXUPPER 'X'

int		ft_printf(const char *str, ...);

//specifier print functions
int		ft_print_dec(va_list args, int *i);
int		ft_print_str(char *s, int *i);
int		ft_print_int(va_list args, int *i);
int		ft_print_char(va_list args, int *i);
int		ft_print_uint(va_list args, int *i);
int		ft_print_hexup(unsigned int num, int *i);
int		ft_print_hexlow(unsigned int num, int *i);
int		ft_print_pointer(va_list args, int *i);

//functional funcs
void	ft_conversions(va_list args, char c, int *i, int *total);
int		ft_process_specifier(va_list args, const char *str, int size);

//helpers
int		ft_convert_hex(unsigned long int n, int flag);
int		ft_check_char(char c, const char *set);
int		ft_hex_len(unsigned	int num);
int		ft_uint_len(unsigned int n);
int		ft_min_max(long n);
int		ft_ptr_len(long n);
int		ft_int_len(int n);
void	ft_putuint_fd(unsigned int n, int fd);
char	*ft_hex_to_charup(unsigned long num);
char	*ft_hex_to_char(unsigned long n);
char	*ft_strrev(char **s);

#endif
