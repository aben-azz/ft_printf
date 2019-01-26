/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 08:43:19 by aben-azz          #+#    #+#             */
/*   Updated: 2019/01/26 19:16:43 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include "ft_printf.h"

t_ype g_type[] = {
	{C_, &print_char},
	{S_, &print_string},
	{P_, &print_pointer},
	{F_, &print_float},
	{D_, &print_signed_integer},
	{I_, &print_signed_integer},
	{HIGHO_, &print_high_octal},
	{LOWO_, &print_low_octal},
	{U_, &print_unsigned_integer},
	{HIGHX_, &print_high_hexadecimal},
	{LOWX_, &print_low_hexadecimal}
};

int	splice(char *string, int precision, int v)
{
	char *l;

	l = ft_strsub(string, 0, ~precision ? precision : ft_strlen(string));
	v ? ft_putstr(l) : NULL;
	return (ft_strlen(l));
}

int		print_char(va_list list, t_fmt fmt)
{
	int		l;
	char	n;

	n = (char)va_arg(list, int);
	l = 0;
	fmt.options & SUB ? ft_putchar(n) : NULL;
	l += ft_repeat_char(fmt.options & ZERO ? '0' : ' ', fmt.minimal_length - 1);
	!(fmt.options & SUB) ? ft_putchar(n) : NULL;
	return (l + 1);
}

int		print_string(va_list list, t_fmt fmt)
{
	int		l;
	char	*string;

	l = 0;
	string = va_arg(list, char*);
	l += fmt.options & SUB ? splice(string, fmt.precision, 1) : 0;
	l += ft_repeat_char(fmt.options & ZERO ? '0' : ' ',
		fmt.minimal_length - splice(string, fmt.precision, 0));
	l += !(fmt.options & SUB) ? splice(string, fmt.precision, 1) : 0;
	return (l);
}

int		print_pointer(va_list list, t_fmt fmt)
{
	display_fmt(fmt);
	(void)list;
	printf("%p", va_arg(list, void*));
	(void)fmt;
	return (0);
}

int		print_float(va_list list, t_fmt fmt)
{
	display_fmt(fmt);
	(void)list;
	printf("%f", (float)va_arg(list, double));
	(void)fmt;
	return (0);
}

int		print_signed_integer(va_list list, t_fmt fmt)
{
	display_fmt(fmt);
	(void)list;
	printf("%d", va_arg(list, int));
	(void)fmt;
	return (0);
}

int		print_unsigned_integer(va_list list, t_fmt fmt)
{
	display_fmt(fmt);
	(void)list;
	printf("%u", va_arg(list, unsigned int));
	(void)fmt;
	return (0);
}

int		print_high_octal(va_list list, t_fmt fmt)
{
	display_fmt(fmt);
	(void)list;
	printf("%O", );
	ft_putstr(ft_itoa_base(va_arg(list, int), 8, 0));
	(void)fmt;
	return (0);
}

int		print_low_octal(va_list list, t_fmt fmt)
{
	display_fmt(fmt);
	(void)list;
	//printf("%o", va_arg(list, int));
	ft_putstr(ft_itoa_base(va_arg(list, int), 8, 1));
	(void)fmt;
	return (0);
}

int		print_low_hexadecimal(va_list list, t_fmt fmt)
{
	display_fmt(fmt);
	(void)list;
	//printf("String: |%s|\n", fmt.string);
	ft_putstr(ft_itoa_base(va_arg(list, int), 16, 1));
	(void)fmt;
	return (0);
}

int		print_high_hexadecimal(va_list list, t_fmt fmt)
{
	display_fmt(fmt);
	(void)list;
	//printf("%X", va_arg(list, int));
	ft_putstr(ft_itoa_base(va_arg(list, int), 16, 0));
	(void)fmt;
	return (0);
}

int		*count_flags(char *string, int index)
{
	static	int			values[2];
	int					offset;

	values[0] = 0;
	values[1] = 0;
	offset = index;
	while (*(string + offset))
	{
		if (*(string + offset) == '%' && *(string + offset + 1) != '%')
			(!values[1]++) && (values[0] = offset++);
		offset += (*(string + offset) == '%') + 1;
	}
	return (values);
}

int		get_precision(char *string)
{
	int n;
	int i;

	i = 0;
	if (!~(n = ft_indexof(string, '.')))
		return (-1);
	while (ft_isdigit(string[n + i]))
		(void)i++;
	return (ft_atoi(ft_strsub(string, n, i)));
}

int		get_minimal_length(char *string)
{
	int n;
	int i;

	i = 1;
	n = ft_indexof(string, '.');
	while ((!ft_isdigit(string[i]) || string[i] == '0') && string[i])
		(void)(string[i++]);
	if (i >= n && ~n)
		return (0);
	n = 0;
	while (ft_isdigit(string[n + i]) && string[i + n])
		(void)(string[n++ + i]);
	return (ft_atoi(ft_strsub(string, i, n)));
}

int		get_length(char *s)
{
	int n;
	int i;

	i = 0;
	n = 0;
	while (!~ft_indexof(LENGTH, s[n++]) && s[n])
		(void)i++;
	if (~(n = ft_indexof(LENGTH, s[i])))
		return (ft_count(s, s[i]) ? (1 << (n)) + (ft_count(s, s[i]) % 2) : -1);
	else
		return (-1);
}

int		get_type(char *str, int i)
{
	return (1 << (ft_indexof(TYPES, str[i - 1]) - 1));
}

int		get_options(char *str)
{
	int		s;
	int		i;
	int		index;

	i = -1;
	s = 0;
	while (OPTIONS[++i])
		if (~(index = ft_indexof(str, OPTIONS[i])) && ft_isdigit(str[index]))
			(s |= (1 << i));
	return (s ? s : 0);
}

int		get_string(char *string)
{
	int i;

	i = count_flags(string, 0)[0];
	while (!~ft_indexof(TYPES, string[i++]))
		(void)i;
	return (i);
}

t_fmt	format(char *string)
{
	return ((t_fmt) {
		.precision = get_precision(string),
		.length = get_length(string),
		.minimal_length = get_minimal_length(string),
		.options = get_options(string),
		.string = string,
		.index = get_string(string),
		.type = get_type(string, get_string(string))
	});
}

int		display_string(char *string, int index, int to)
{
	ft_putstr(ft_strsub(string, index, ~to ? to : ft_strlen(string) - index));
	return (0);
}

void	view_fmt(t_fmt *flags, int length)
{
	int i;

	i = -1;
	while (++i < length)
		printf("Tour de boucle %i %i,%i,%i,%i,%i,%s,\n", i, flags[i].precision,
			flags[i].length, flags[i].type, flags[i].minimal_length,
			flags[i].options, flags[i].string);
}

void	display_fmt(t_fmt format)
{
	format.length == L_ && printf("L\n");
	format.length == LL_ && printf("LL\n");
	format.length == H_ && printf("H\n");
	format.length == HH_ && printf("HH\n");
	C_ == format.type && printf("C\n");
	S_ == format.type && printf("S\n");
	P_ == format.type && printf("P\n");
	F_ == format.type && printf("F\n");
	D_ == format.type && printf("D\n");
	I_ == format.type && printf("I\n");
	HIGHO_ == format.type && printf("O\n");
	U_ == format.type && printf("U\n");
	HIGHX_ == format.type && printf("X\n");
	LOWO_ == format.type && printf("O\n");
	LOWX_ == format.type && printf("x\n");
	printf("format de %d\n", format.options);
	(format.options & HASH) && printf("#\n");
	(format.options & SUB) && printf("-\n");
	(format.options & ZERO) && printf("0\n");
	(format.options & ADD) && printf("+\n");
	(format.options & SPACE) && printf("SPACE\n");
	printf("Precision de |%d|\n", format.precision);
	printf("Champs de |%d|\n", format.minimal_length);
	printf("String |%s|\n", format.string);
	printf("Index de |%d|\n", format.index);
}

t_fmt	*get_flags(char *s, int n)
{
	int		i;
	int		next;
	int		j;
	t_fmt	*flags;

	j = 0;
	if (!(flags = ft_memalloc(sizeof(t_fmt) * n)) || !n)
		return (0);
	i = count_flags(s, 0)[0];
	i && display_string(s, 0, i);
	while (n-- > 0)
	{
		next = count_flags(s, i + 1)[0];
		flags[j++] = format(ft_strsub(s, i,
			!n ? (int)ft_strlen(s) - i : next - i));
		i += (next - i);
	}
	return (flags);
}

int		ft_printf(const char *format, ...)
{
	int		length;
	int		i;
	int		j;
	va_list	ap;
	t_fmt *flags;

	i = -1;
	length = count_flags((char*)format, 0)[1];
	flags = get_flags((char*)format, length);
	va_start(ap, format);
	if (!(count_flags((char*)format, 0)[0] + count_flags((char*)format, 0)[1]))
	{
		display_string((char*)format, 0, -1);
		return (ft_strlen((char*)format));
	}
	while (++i < length)
	{
		j = -1;
		while (g_type[++j].type)
		{
			if (g_type[j].type == flags[i].type)
			{
				g_type[j].function(ap, flags[i]);
				display_string(flags[i].string, flags[i].index, -1);
				break ;
			}
		}
	}
	va_end(ap);
	return (length);
}
