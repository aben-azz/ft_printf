/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 08:43:19 by aben-azz          #+#    #+#             */
/*   Updated: 2019/02/06 03:16:00 by aben-azz         ###   ########.fr       */
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
	l += ft_repeat_char(fmt.opt & ZERO && (~fmt.opt & SUB) ? '0' : ' ',
		fmt.field - splice(string, fmt.precision, 0));
	l += !(fmt.opt & SUB) ? splice(string, fmt.precision, 1) : 0;
	printf("\n%d\n", l);
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
	return ((int)ft_strlen(l));
}

int		print_float(va_list list, t_fmt fmt)
{
	int args;
	int len;
	char *str;
	double number;
	int champs;
	int length = 0;

	number = fmt.length == LU_ ? va_arg(list, long double) : va_arg(list, double);
	len = intlen(number) + 2 + (~fmt.precision ? fmt.precision : 6);
	if (!(str = malloc(len)))
		return (0);
	args = fmt.field - (len + 1) ? fmt.field - len + 1 : 2;
	int prec;

	prec = (fmt.precision >= intlen(number) ? fmt.precision - intlen(number) : -1);
	if (number < 0.0)
		prec++;
	champs = (fmt.field >= intlen(number) ? fmt.field - intlen(number) : 0);
	champs -= (~prec ? prec : 0);
	champs += (number >= 0 && fmt.opt & ADD);
	length += intlen(number) + champs;
	ft_ftoa(number, ~fmt.precision ? fmt.precision : 6, str);
	if (fmt.opt & SUB)
	{
		if (number < 0)
			ft_putchar('-');
		else if (number >= 0.0 && (fmt.opt & ADD || (fmt.opt & SPACE)))
		{
			ft_putchar(fmt.opt & ADD ? '+' : ' ');
			champs -= 2;
			fmt.opt & ADD || champs++;
		}
		ft_putstr(str);
		ft_repeat_char(' ', champs);
	}
	else
	{
		if (fmt.precision)
		{
			champs -= 4;
			if (fmt.opt & ADD && number < 0.0)
				champs += 2;
			if (fmt.opt & SPACE && (fmt.opt & ZERO) && number == 0.0)
			{
				args--;
				(fmt.opt & SPACE) ? ft_putchar(' ') : NULL;
			}
			if (fmt.opt & ADD && number >= 0.0)
				args--;
			if ((fmt.opt & ZERO) && (fmt.opt & SPACE) && number > 0.0)
			{
				(~fmt.opt & ADD) ? ft_putchar(' ') : NULL;
				args--;
			}
			if ((fmt.opt & ZERO) && (fmt.opt & SPACE) && number >= 0.0 && (fmt.opt & ADD))
			{
				number == 0.0 ? ft_putchar(' ') : NULL;
				args++;
			}
			if (~fmt.opt & ZERO)
				ft_repeat_char(' ', args);
			if (number < 0.0)
				ft_putchar('-');
			else if (fmt.opt & ADD)
				ft_putchar('+');
			if (fmt.opt & ZERO)
				ft_repeat_char('0', args);
			ft_putstr(str);
		}
		else
		{
			printf("la mon pti pote xd\n");
			if (number > 0.0 && (fmt.opt & ADD))
				champs -= 2;
			if (fmt.opt & SPACE && number >= 0.0 && (~fmt.opt & ADD))
			{
				champs--;
				ft_putchar(' ');
			}
			(~fmt.opt & ZERO) && ft_repeat_char(' ', champs);
			if (number < 0.0)
				ft_putchar('-');
			else if (fmt.opt & ADD)
				ft_putchar('+');
			(fmt.opt & ZERO) && ft_repeat_char('0', champs);
			ft_putstr(str);
		}
	}
	return (0);
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
int		print_signed_integer(va_list list, t_fmt fmt)
{
	//display_fmt(fmt);
	long long number;
	int length = 0;
	if (fmt.length == HH_)
		number = (char)va_arg(list, long long);
	else if (fmt.length == H_)
		number = (short)va_arg(list, long long);
	else if (fmt.length == L_ || fmt.length == LL_)
		number = va_arg(list, long long);
	else
		number = va_arg(list, int);
	int champs;
	int prec;

	prec = (fmt.precision >= intlen(number) ? fmt.precision - intlen(number) : -1);
	if (number < 0)
		prec++;
	champs = (fmt.field >= intlen(number) ? fmt.field - intlen(number) : 0);
	champs -= (~prec ? prec : 0);
	champs += (number >= 0 && fmt.opt & ADD);
	length += intlen(number) + champs;
	if (fmt.opt & SUB)
	{
		if (number < 0)
			ft_putchar('-');
		else if (number >= 0 && (fmt.opt & ADD || (fmt.opt & SPACE)))
		{
			ft_putchar(fmt.opt & ADD ? '+' : ' ');
			champs -= 2;
			fmt.opt & ADD || champs++;
		}
		if (~prec)
			ft_repeat_char('0', prec);
		pf_putnbr(number);
		ft_repeat_char(' ', champs);
	}
	else
	{
		if (~fmt.precision)
		{
			if (number > 0 && (fmt.opt & ADD))
				champs -= 2;
			ft_repeat_char(' ', champs);
			if (number < 0)
				ft_putchar('-');
			else if (fmt.opt & ADD)
				ft_putchar('+');
			ft_repeat_char('0', prec);
			pf_putnbr(number);
		}
		else
		{
			if (number > 0 && (fmt.opt & ADD))
				champs -= 2;
			if (fmt.opt & SPACE && number > 0 && (~fmt.opt & ADD))
			{
				champs--;
				ft_putchar(' ');
			}
			if (number < 0)
				ft_putchar('-');
			else if (fmt.opt & ADD)
				ft_putchar('+');
			ft_repeat_char('0', champs);
			pf_putnbr(number);
		}
	}
	return (0);
}
int		print_unsigned_integer(va_list list, t_fmt fmt)
{
	long long n;
	int length;
	int champs;
	int prec;

	length = 0;
	if (fmt.length == HH_)
		n = (char)va_arg(list, unsigned long long);
	else if (fmt.length == H_)
		n = (short)va_arg(list, unsigned long long);
	else if (fmt.length == L_ || fmt.length == LL_)
		n = va_arg(list, unsigned long long);
	else
		n = va_arg(list, unsigned int);
	prec = (fmt.precision >= intlen(n) ? fmt.precision - intlen(n) : -1);
	if (n < 0)
		prec++;
	champs = (fmt.field >= intlen(n) ? fmt.field - intlen(n) : 0);
	champs -= (~prec ? prec : 0);
	champs += (n >= 0 && fmt.opt & ADD);
	length += intlen(n) + champs;
	if (fmt.opt & SUB)
	{
		if (n > 0 && (fmt.opt & ADD))
			champs -= 1;
		if (~prec)
			ft_repeat_char('0', prec);
		pf_putnbr(n);
		ft_repeat_char(' ', champs);
	}
	else
	{
		if (~fmt.precision)
		{
			if (n > 0 && (fmt.opt & ADD))
				champs -= 1;
			ft_repeat_char(' ', champs);
			if (n < 0)
				ft_putchar('-');
			ft_repeat_char('0', prec);
			pf_putnbr(n);
		}
		else
		{
			if (n > 0 && (fmt.opt & ADD))
				champs -= 2;
			if (fmt.opt & SPACE && n > 0 && (~fmt.opt & ADD))
			{
				champs--;
				ft_putchar(' ');
			}
			ft_repeat_char('0', champs);
			pf_putnbr(n);
		}
	}
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
					l += g_type[j].function ? g_type[j].function(ap, flags[i]) : 0;
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
