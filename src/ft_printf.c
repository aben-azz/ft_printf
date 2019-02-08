/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 08:43:19 by aben-azz          #+#    #+#             */
/*   Updated: 2019/02/08 07:23:47 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include "ft_printf.h"

t_ype g_type[] = {
	{C_, &print_char},
	{S_, &print_string},
	{LOWP_, &print_pointer},
	{HIGHP_, &print_pointer},
	{F_, &print_float},
	{D_, &print_signed_integer},
	{I_, &print_signed_integer},
	{O_, &print_octal},
	{U_, &print_unsigned_integer},
	{HIGHX_, &print_hexadecimal},
	{LOWX_, &print_hexadecimal},
};

intmax_t    get_signed(t_fmt *fmt, va_list ap)
{
	if (fmt->length == HH_)
		return ((char)va_arg(ap, long long));
	else if (fmt->length == H_)
		return ((short)va_arg(ap, long long));
	else if (fmt->length == L_ || fmt->length == LL_)
		return (va_arg(ap, long long));
	else if (fmt->length == Z_)
		return (va_arg(ap, size_t));
	else if (fmt->length == J_)
		return (va_arg(ap, intmax_t));
	else
		return (va_arg(ap, int));
	return (0);
}

uintmax_t    get_unsigned(t_fmt *fmt, va_list ap)
{
	if (fmt->length == L_ || fmt->length == LL_ || fmt->type == LOWP_
			|| fmt->type == HIGHP_)
		return ((unsigned short)va_arg(ap, unsigned long long));
	else if (fmt->length == HH_)
		return ((unsigned char)va_arg(ap, unsigned long long));
	else if (fmt->length == H_)
		return (va_arg(ap, unsigned long long));
	else if (fmt->length == Z_)
		return (va_arg(ap, size_t));
	else if (fmt->length == J_)
		return (va_arg(ap, uintmax_t));
	else
		return (va_arg(ap, unsigned int));
	return (0);
}

char		*ft_utoa_base(uintmax_t nb, int base, int uppercase)
{
	//printf("[%ju,%d]\n", nb, base);
	char	*output;
	int		digits;

	if (nb == 0)
		return (ft_strdup("0"));
	digits = ft_intlen_base(nb, base);
	output = ft_strnew(digits);
	while (digits--)
	{
		output[digits] = (nb % base) +
			(nb % base > 9 ? "aA"[uppercase] - 10 : '0');
		nb /= base;
	}
	return (output);
}

char *get_s(t_fmt *fmt, va_list ap)
{
	char *str;
	char b;
	char uppercase;

	uppercase = 0;
	b = 10;
	(fmt->type == HIGHX_ || fmt->type == LOWX_ || fmt->type == LOWP_ ||
			fmt->type == HIGHP_) && (b = 16);
	(fmt->type == HIGHX_ || fmt->type == HIGHP_) && (uppercase = 1);
	(fmt->type == O_) && (b = 8);
	if (fmt->type == F_)
	{
		str = malloc(100);
		if (fmt->length == LU_)
			ft_ftoa(va_arg(ap, long double),
				!~fmt->precision ? 6 : fmt->precision, str);
		else
			ft_ftoa(va_arg(ap, double),
				!~fmt->precision ? 6 : fmt->precision, str);
	}
	else
	{
		//printf("\nupperacse: %c, base: %c\n", uppercase, b);
		if (fmt->type == D_ || fmt->type == I_)
			str = ft_itoa_base(get_signed(fmt, ap), b, uppercase);
		else
		{
			str = ft_utoa_base(get_unsigned(fmt, ap), b, uppercase);
		//printf("\n{%d,%d}\n", uppercase, b);
		}
	}
	!str ? exit(0) : NULL;
	return (str);
}



int		print_char(va_list list, t_fmt *fmt)
{
	int		l;
	char	n;

	n = (char)va_arg(list, int);
	l = 0;
	fmt->opt & SUB ? ft_putchar(n) : NULL;
	l += ft_repeat_char(fmt->opt & ZERO ? '0' : ' ', fmt->field - 1);
	!(fmt->opt & SUB) ? ft_putchar(n) : NULL;
	return (l + 1);
}

int		print_string(va_list list, t_fmt *fmt)
{
	int		l;
	char	*string;

	l = 0;
	string = va_arg(list, char*);
	l += fmt->opt & SUB ? splice(string, fmt->precision, 1) : 0;
	l += ft_repeat_char(fmt->opt & ZERO && (~fmt->opt & SUB) ? '0' : ' ',
		fmt->field - splice(string, fmt->precision, 0));
	l += !(fmt->opt & SUB) ? splice(string, fmt->precision, 1) : 0;
	printf("\n%d\n", l);
	return (l);
}
int lol(t_fmt *fmt, char *str, int len, char signe)
{
	int ret;

	ret = 0;
	//printf("len: %d\nfmt.precision: %d\nfield: %d\n", len, fmt->precision, fmt->field);
	if (fmt->opt & SUB)
	{
		signe == '-' ? ft_putchar(signe) : NULL;
		(signe == '+' && (fmt->opt & ADD)) ? ft_putchar(signe) : 0;
		//if (fmt->prefixe)
			//ret = print_prefixe(fmt->conversion);
		ft_repeat_char('0', fmt->field);
		ft_putstr(str);
		ft_repeat_char(' ', len);
	}
	else
	{
		~(fmt->opt & ZERO) && ft_repeat_char(' ', len);
		signe == '-' ? ft_putchar(signe) : NULL;
		signe == '+' && fmt->opt & ADD ? ft_putchar(signe) : NULL;
		//if (fmt->prefixe)
			//ret = print_prefixe(fmt->conversion);
		//fmt->opt & ZERO ? ft_nputchar(3, len) : NULL;
		ft_repeat_char('0', fmt->field);
		ft_putstr(str);
	}
	len = len < 0 ? 0 : len;
	if (signe == '+' && (fmt->opt & ADD))
		len++;
	//printf("len{%d} + signe{%c}\n", len, fmt->field);
	return (ret + ft_strlen(str) + len + fmt->field + (signe == '-' ? 1 : 0));
}


int	splice(char *string, int precision, int v)
{
	char *l;

	l = ft_strsub(string, 0, ~precision ? precision : ft_strlen(string));
	v ? ft_putstr(l) : NULL;
	return ((int)ft_strlen(l));
}

int format_width(char *string, t_fmt *fmt)
{
	int len;
	len = fmt->field - ft_strlen(string) - (fmt->signe == '-' ? 1 : 0);
	if (fmt->opt & ADD)
		fmt->signe == '+' && len--;
	if (fmt->type == F_)
	{
		if (~fmt->opt & ZERO && fmt->type == F_)
			fmt->field = 0;
		else
		{
			len = 0;
			fmt->field -= ft_strlen(string) + (fmt->signe == '-' ? 1 : 0);
		}
	}
	else
	{
		fmt->field = fmt->precision - (ft_strlen(string));
		//printf("{%d}", fmt->field);
		fmt->field = fmt->field > 0 ? fmt->field : 0;
		len -= fmt->field;
		//if (fmt->precision <= 0)
			//len -= ~fmt->precision ? ft_strlen(string) : ft_strlen(string) + 1;
		if (fmt->opt & ZERO && (!~fmt->precision))
		{

			fmt->field = len;
			len = 0;
		}
	}
	return (len);
}


int		print_pointer(va_list list, t_fmt *fmt)
{
	char *string;
	int len;

	string = get_s(fmt, list);
	fmt->signe = 0;
	len = format_width(string, fmt);
	return (lol(fmt, string, len, fmt->signe));
}

int		print_float(va_list list, t_fmt *fmt)
{
	char *string;
	int len;

	string = get_s(fmt, list);
	fmt->signe = '+';
	(*string == '-') && (fmt->signe = '-');
	(*string == '-') && string++;
	len = format_width(string, fmt);
	return (lol(fmt, string, len, fmt->signe));
}

int		print_signed_integer(va_list list, t_fmt *fmt)
{
	char *string;
	int len;

	string = get_s(fmt, list);
	fmt->signe = '+';
	(*string == '-') && (fmt->signe = '-');
	(*string == '-') && string++;
	len = format_width(string, fmt);
	return (lol(fmt, string, len, fmt->signe));
}

void	pf_putnbr(long long n)
{
	if (n < 0)
	{
		(n < -9223372036854775807) ? ft_putchar('2') : NULL;
		(n < -9223372036854775807) && (n = -223372036854775808);
		n = -n;
	}
	(n > 9) ? ft_putnbr(n / 10) : NULL;
	ft_putchar(48 + n % 10);
}

int		print_unsigned_integer(va_list list, t_fmt *fmt)
{
	char *string;
	int len;

	string = get_s(fmt, list);
	fmt->signe = 0;
	len = format_width(string, fmt);
	return (lol(fmt, string, len, fmt->signe));
}

int		print_octal(va_list list, t_fmt *fmt)
{
	char *string;
	int len;

	string = get_s(fmt, list);
	fmt->signe = 0;
	len = format_width(string, fmt);
	return (lol(fmt, string, len, fmt->signe));
}

int		print_hexadecimal(va_list list, t_fmt *fmt)
{
	char *string;
	int len;

	string = get_s(fmt, list);
	fmt->signe = 0;
	len = format_width(string, fmt);
	return (lol(fmt, string, len, fmt->signe));
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
	{
		ft_putstr(ft_strsub(string, index, to));
		return (to);
	}
	else
		while (*(string + index))
			ft_putchar(*(string + index++));
	return (index);
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

void	display_fmt(t_fmt *format)
{
	printf("FORMAT____________________\n");
	format->length == L_ && printf("L\n");
	format->length == LL_ && printf("LL\n");
	format->length == H_ && printf("H\n");
	format->length == HH_ && printf("HH\n");
	format->length == LU_ && printf("LU\n");
	C_ == format->type && printf("C\n");
	S_ == format->type && printf("S\n");
	LOWP_ == format->type && printf("p\n");
	HIGHP_ == format->type && printf("P\n");
	F_ == format->type && printf("F\n");
	D_ == format->type && printf("D\n");
	I_ == format->type && printf("I\n");
	U_ == format->type && printf("U\n");
	HIGHX_ == format->type && printf("X\n");
	O_ == format->type && printf("O\n");
	LOWX_ == format->type && printf("x\n");
	printf("format de %d\n", format->opt);
	(format->opt & HASH) && printf("#\n");
	(format->opt & SUB) && printf("-\n");
	(format->opt & ZERO) && printf("0\n");
	(format->opt & ADD) && printf("+\n");
	(format->opt & SPACE) && printf("SPACE\n");
	printf("Precision de |%d|\n", format->precision);
	printf("Champs de |%d|\n", format->field);
	printf("String |%s|\n", format->string);
	printf("Index de |%d|\n", format->index);
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

int		parse(const char *format, va_list ap)
{
	int i = -1;
	int length = 0;
	int j;
	t_fmt *flags;
	int l = 0;
	length = count_flags((char*)format, 0)[1];
	flags = get_flags((char*)format, length);
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
					g_type[j].function ? g_type[j].function(ap, &flags[i]) : 0;
					l += display_string(flags[i].string, flags[i].index, -1);
					break ;
				}
			}
		}
	}

	return (l);
}

int		ft_printf(const char *format, ...)
{
	int		length;
	va_list	ap;

	va_start(ap, format);
	length = parse(format, ap);
	va_end(ap);
	//printf("Longueur de %d\n", length);
	return (length);
}
