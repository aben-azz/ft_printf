/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 08:43:19 by aben-azz          #+#    #+#             */
/*   Updated: 2019/02/03 03:13:31 by aben-azz         ###   ########.fr       */
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
	{O_, &print_octal},
	{U_, &print_unsigned_integer},
	{HIGHX_, &print_high_hexadecimal},
	{LOWX_, &print_low_hexadecimal},
};

int		print_char(va_list list, t_fmt fmt)
{
	int		l;
	char	n;

	n = (char)va_arg(list, int);
	l = 0;
	fmt.opt & SUB ? ft_putchar(n) : NULL;
	l += ft_repeat_char(fmt.opt & ZERO ? '0' : ' ', fmt.field - 1);
	!(fmt.opt & SUB) ? ft_putchar(n) : NULL;
	return (l + 1);
}

int		print_string(va_list list, t_fmt fmt)
{
	int		l;
	char	*string;

	l = 0;
	string = va_arg(list, char*);
	l += fmt.opt & SUB ? splice(string, fmt.precision, 1) : 0;
	l += ft_repeat_char(fmt.opt & ZERO ? '0' : ' ',
		fmt.field - splice(string, fmt.precision, 0));
	l += !(fmt.opt & SUB) ? splice(string, fmt.precision, 1) : 0;
	return (l);
}

int		print_pointer(va_list list, t_fmt fmt)
{
	(void)list;
	printf("%#x", va_arg(list, unsigned int));
	(void)fmt;
	return (0);
}

int	splice(char *string, int precision, int v)
{
	char *l;

	l = ft_strsub(string, 0, ~precision ? precision : ft_strlen(string));
	v ? ft_putstr(l) : NULL;
	return (ft_strlen(l));
}

int		print_float(va_list list, t_fmt fmt)
{
	int l;
	double num;
	int len;
	int args[2];
	char *str;

	l = 0;
	num = fmt.length == LU_ ? va_arg(list, long double) : va_arg(list, double);
	len = intlen(num) + 2 + (~fmt.precision ? fmt.precision : 6);
	args[0] = fmt.field - (len + 1) ? fmt.field - len + 1 : 2;
	args[1] = fmt.opt;
	if (!(str = malloc(len)))
		return (0);
	(fmt.opt & SPACE && num > 0.0) && args[0]--;
	((fmt.opt & SPACE && (fmt.opt & SUB) && num > 0.0)) && write(1, " ", 1);
	((fmt.opt & SPACE && (fmt.opt & SUB) && num > 0.0)) && fmt.field++;
	ft_ftoa(num, ~fmt.precision ? fmt.precision : 6, str, args);
	if(fmt.opt & SPACE && num > 0.0 && (int)ft_strlen(str) > fmt.field && ~fmt.opt & SUB)
		write(1, " ", 1);
	(fmt.opt & SUB) ? ft_putstr(str) : 0;
	ft_repeat_char(' ', fmt.field - ft_strlen(str) - (((fmt.opt & SUB) && (fmt.opt & SPACE) && num > 0.0) ? 2 : 0));
	!(fmt.opt & SUB) ? ft_putstr(str) : 0;
	return (l);
}
int		print_signed_integer(va_list list, t_fmt fmt)
{
	//display_fmt(fmt);
	long long number;
	if (fmt.length == HH_)
		number = (char)va_arg(list, long long);
	else if (fmt.length == H_)
		number = (short)va_arg(list, long long);
	else if (fmt.length == L_ || fmt.length == LL_)
		number = va_arg(list, long long);
	else
		number = va_arg(list, int);
	ft_putnbr(number);
	return (0);
}

int		print_unsigned_integer(va_list list, t_fmt fmt)
{
	//display_fmt(fmt);
	(void)list;
	printf("%u", va_arg(list, unsigned int));
	(void)fmt;
	return (0);
}
int		print_octal(va_list list, t_fmt fmt)
{
	//display_fmt(fmt);
	(void)list;
	(fmt.opt & HASH) ? ft_putstr("0") : NULL;
	ft_putstr(ft_itoa_base(va_arg(list, int), 8, 0));
	(void)fmt;
	return (0);
}


int		print_low_hexadecimal(va_list list, t_fmt fmt)
{
	//display_fmt(fmt);
	(void)list;
	(fmt.opt & HASH) ? ft_putstr("0x") : NULL;
	ft_putstr(ft_itoa_base(va_arg(list, int), 16, 1));
	(void)fmt;
	return (0);
}

int		print_high_hexadecimal(va_list list, t_fmt fmt)
{
	//display_fmt(fmt);
	(void)list;
	(fmt.opt & HASH) ? ft_putstr("0X") : NULL;
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
	//printf(" n est a %d, <%s>\n", n, string);
	while (ft_isdigit(string[n + i]))
		(void)i++;
	return (ft_atoi(ft_strsub(string, n, i)));
}

int		get_field(char *string)
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
	int	s;
	int	i;
	int	index;

	i = -1;
	s = 0;
	while (OPTIONS[++i])
		if (~(index = ft_indexof(str, OPTIONS[i])) &&
			(i != 1 || !ft_isdigit(str[index - 2])))
			(s |= (1 << i));
	return (s ? s : 0);
}

int		get_string(char *string)
{
	int i;

	i = count_flags(string, 0)[0];
	while (!~ft_indexof(TYPES, string[i++]) && string[i])
		(void)i;
	return (i);
}

t_fmt	format(char *string)
{
	return ((t_fmt) {
		.precision = get_precision(string),
		.length = get_length(string),
		.field = get_field(string),
		.opt = get_options(string),
		.string = string,
		.index = get_string(string),
		.type = get_type(string, get_string(string))
	});
}

int		display_string(char *string, int index, int to)
{
	if (to > index)
		ft_putstr(ft_strsub(string, index, to));
	else
		while (*(string + index))
			ft_putchar(*(string + index++));
	return (0);
}

void	view_fmt(t_fmt *flags, int length)
{
	int i;

	i = -1;
	while (++i < length)
		printf("Tour de boucle %i %i,%i,%i,%i,%i,%s,\n", i, flags[i].precision,
			flags[i].length, flags[i].type, flags[i].field,
			flags[i].opt, flags[i].string);
}

void	display_fmt(t_fmt format)
{
	printf("FORMAT____________________\n");
	format.length == L_ && printf("L\n");
	format.length == LL_ && printf("LL\n");
	format.length == H_ && printf("H\n");
	format.length == HH_ && printf("HH\n");
	format.length == LU_ && printf("LU\n");
	C_ == format.type && printf("C\n");
	S_ == format.type && printf("S\n");
	P_ == format.type && printf("P\n");
	F_ == format.type && printf("F\n");
	D_ == format.type && printf("D\n");
	I_ == format.type && printf("I\n");
	U_ == format.type && printf("U\n");
	HIGHX_ == format.type && printf("X\n");
	O_ == format.type && printf("O\n");
	LOWX_ == format.type && printf("x\n");
	printf("format de %d\n", format.opt);
	(format.opt & HASH) && printf("#\n");
	(format.opt & SUB) && printf("-\n");
	(format.opt & ZERO) && printf("0\n");
	(format.opt & ADD) && printf("+\n");
	(format.opt & SPACE) && printf("SPACE\n");
	printf("Precision de |%d|\n", format.precision);
	printf("Champs de |%d|\n", format.field);
	printf("String |%s|\n", format.string);
	printf("Index de |%d|\n", format.index);
	printf("FORMAT____________________\n");
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
			//display_fmt(flags[j-1]);
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
		//printf("xd");
		display_string((char*)format, 0, -1);
		return (ft_strlen((char*)format));
	}
	while (++i < length)
	{
		//display_fmt(flags[j]);
		j = -1;
		if (flags[i].type == 1 << 30){
			printf("Non reconnu\n");
		}
		else
		{
			while (g_type[++j].type)
			{
				if (g_type[j].type == flags[i].type)
				{
					g_type[j].function && g_type[j].function(ap, flags[i]);
					display_string(flags[i].string, flags[i].index, -1);
					break ;
				}
			}
		}
	}
	va_end(ap);
	return (length);
}
