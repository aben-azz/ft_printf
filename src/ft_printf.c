/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 08:43:19 by aben-azz          #+#    #+#             */
/*   Updated: 2019/02/27 02:33:21 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include "ft_printf.h"

t_ype g_type[] = {
	{C_, &handle_char},
	{PERCENT_, &handle_char},
	{S_, &handle_string},
	{LOWP_, &handle_number},
	{HIGHP_, &handle_number},
	{F_, &handle_number},
	{D_, &handle_number},
	{I_, &handle_number},
	{O_,&handle_number},
	{U_, &handle_number},
	{HIGHX_, &handle_number},
	{LOWX_, &handle_number},
	{B_, &handle_number},
	{V_, &handle_array},
	{R_, &handle_array}
};

intmax_t		get_signed(t_fmt *fmt, va_list ap)
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

uintmax_t		get_unsigned(t_fmt *fmt, va_list ap)
{
	if (fmt->length == L_ || fmt->length == LL_ || fmt->type == LOWP_
			|| fmt->type == HIGHP_)
		return (va_arg(ap, unsigned long long));
	else if (fmt->length == H_)
		return ((unsigned short)va_arg(ap, unsigned long long));
	else if (fmt->length == HH_)
		return ((unsigned char)va_arg(ap, unsigned long long));
	else if (fmt->length == Z_)
		return (va_arg(ap, size_t));
	else if (fmt->length == J_)
		return (va_arg(ap, uintmax_t));
	else
		return (va_arg(ap, unsigned int));
	return (0);
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
	(fmt->type == B_) && (b = 2);
	if (fmt->type == F_)
	{
		if (fmt->length == LU_)
			str = ft_ftoa(va_arg(ap, long double),
				!~fmt->precision ? 6 : fmt->precision);
		else
			str = ft_ftoa(va_arg(ap, double),
				!~fmt->precision ? 6 : fmt->precision);
	}
	else
	{
		if (fmt->type == D_ || fmt->type == I_)
			str = ft_itoa_base(get_signed(fmt, ap), b, uppercase);
		else
			str = ft_utoa_base(get_unsigned(fmt, ap), b, uppercase);
	}
	!str ? exit(0) : NULL;
	return (str);
}

int		handle_char(va_list list, t_fmt *fmt)
{

	char	c;

	if (fmt->type == C_)
		c = (char)va_arg(list, int);
	else
		c = '%';
	if (fmt->opt & SUB)
	{
		ft_putchar(c);
		ft_repeat_char(' ', fmt->field - 1);
	}
	else
	{
		ft_repeat_char(fmt->opt & ZERO ? '0' : ' ', fmt->field - 1);
		ft_putchar(c);
	}
	return (fmt->field > 0 ? fmt->field : 1);
}

int		handle_string(va_list list, t_fmt *fmt)
{
	int		l;
	char	*string;

	l = 0;
	string = va_arg(list, char*);
	string = !string ? "(null)" : string;
	fmt->opt & SUB ? splice(string, fmt->precision, 1) : 0;
	l += ft_repeat_char(fmt->opt & ZERO && (~fmt->opt & SUB) ? '0' : ' ',
		fmt->field - splice(string, fmt->precision, 0));
	l = ft_max(l, 0);
	!(fmt->opt & SUB) ? splice(string, fmt->precision, 1) : 0;
	return (l + splice(string, fmt->precision, 0));
}

static int		print_prefixe(int c)
{
	int i;

	i = 0;
	c = (c == LOWP_ || c == HIGHP_) ? LOWX_ : c;
	if (c == O_ || c == LOWX_ || c == HIGHX_)
	{
		ft_putchar('0');
		i++;
	}
	if (c == LOWX_ || c == HIGHX_)
	{
		ft_putchar( c == HIGHX_ ? 'X' :'x');
		i++;
	}
	return (i);
}
int		print_numbers(t_fmt *fmt, char *str, int len)
{
	//printf("{%d,%d}\n", len, fmt->precision);
	int ret;

	ret = 0;
	if (fmt->opt & SUB)
	{
		fmt->signe ? ft_putchar(fmt->signe) : NULL;
		if (fmt->prefixe)
			ret = print_prefixe(fmt->type);
		ft_repeat_char('0', fmt->precision);
		ft_putstr(str);
		ft_repeat_char(' ', len);
	}
	else
	{

		if(~fmt->opt & ZERO)
		{
			 ft_repeat_char(' ', len);
		}
		fmt->signe ? ft_putchar(fmt->signe) : NULL;
		//printf("@\n");
		if (fmt->prefixe)
			ret = print_prefixe(fmt->type);
		//printf("@\n");
		if(fmt->opt & ZERO)
		{
			ft_repeat_char('0', len);
		}
		//printf("@\n");
		ft_repeat_char('0', fmt->precision);



		ft_putstr(str);
	}
	len = len < 0 ? 0 : len;
	return (ret + ft_strlen(str) + len + fmt->precision + (fmt->signe != 0));
}

int		handle_number(va_list ap, t_fmt *fmt )
{
	char		*str;
	int			len;


	(fmt->type != F_ && ~fmt->precision) && (fmt->opt &= ~(ZERO));
	str = get_s(fmt, ap);
	if (!fmt->precision && str[0] == '0' && fmt->type != F_)
	{
		if (fmt->type == HIGHX_ || fmt->type == LOWX_)
			fmt->prefixe = 0;
		str[0] = '\0';
	}
	if (fmt->type != LOWP_ && fmt->type != HIGHP_)
		fmt->prefixe = *str == '0' ? 0 : fmt->prefixe;
	if (*str == '-')
		fmt->signe = *(str++);
	fmt->precision -= ft_strlen(str);
	fmt->precision = fmt->prefixe == 1 ? fmt->precision - 1 : fmt->precision;
	fmt->precision = fmt->precision < 0 ? 0 : fmt->precision;
	len = fmt->field - ft_strlen(str) - (fmt->signe ? 1 : 0) - fmt->precision;
	len -= fmt->prefixe;
	len = print_numbers(fmt, str, len);
	fmt->signe == '-' ? free(--str) : ft_strdel(&str);

	return (len);
}

int		handle_array(va_list list, t_fmt *fmt)
{
	int		*array;
	char	**string;
	int		i;
	char	*separator;
	int		number;

	if (fmt->type == V_)
		array = va_arg(list, int *);
	else
		string = va_arg(list, char **);
	(void)string;
	(void)array;
	number = va_arg(list, int);
	i = 0;
	separator = va_arg(list, char *);
	while (i < number)
	{
		fmt->type == V_ ? ft_putnbr(array[i++]) : ft_putstr(string[i++]);
		i != number ? ft_putstr(separator) : 0;
	}
	return (0);
}

int	splice(char *string, int precision, int v)
{
	char *l;

	l = ft_strsub(string, 0, ~precision ? precision : ft_strlen(string));
	v ? ft_putstr(l) : NULL;
	return ((int)ft_strlen(l));
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

int				get_precision(char *str, t_fmt *fmt, va_list ap)
{
	int precision;
	int point;

	point = 0;
	while (*str && !ft_strchr("diouxXcspfDOUbvr%", *str))
	{
		if (*str == '.' && (point = 1) && str++)
		{
			precision = 0;
			(ft_isdigit(*str)) && (precision = ft_atoi(str));
			while (ft_isdigit(*str))
				str++;
			if (*str == '*' && *(str - 1) == '.' && str++)
			{
				precision = va_arg(ap, int);
				point = precision < 0 ? 0 : point;
			}
			continue;
		}
		str++;
	}
	(!point) && (precision = -1);
	if (!point && fmt->type == F_)
		precision = 6;
	return (precision);
}

int		get_field(char *str, va_list ap)
{
	int width;
	int temp;

	width = 0;
	while (*str && !ft_strchr("diouxXcspfDOUbvr%", *str))
	{
		if (*str == '.' && str++)
		{
			while (ft_isdigit(*str))
				str++;
			str += (*str == '*' && *(str - 1) == '.');
			continue;
		}
		(*str == '*') && (width = va_arg(ap, int));
		//(*str == '*') && (fmt->minus = width < 0 ? '-' : 0);
		(*str == '*') && (width = ABS(width));
		if (ft_isdigit(*str) && (temp = ft_atoi(str)))
		{
			width = temp;
			while (ft_isdigit(*(str + 1)))
				str++;
		}
		str++;
	}
	return (width);
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

int		get_type(char *str)
{
	int i;

	i = 0;
	while (!~ft_indexof("diouxXcspfDOUbvr%", str[i]))
		i++;
	return (1 << (ft_indexof(TYPES, str[i]) - 1));
}

int		get_string(char *string)
{
	int i;

	i = count_flags(string, 0)[0];
	while (!~ft_indexof(TYPES, string[i++]) && string[i])
		(void)i;
	return (i);
}

int		display_string(char *string, int index, int to)
{
	int len;

	len = 0;
	if (to > index)
	{
		ft_putstr(ft_strsub(string, index, to));
		return (to);
	}
	else
		while (*(string + index))
			len += ft_repeat_char(*(string + index++), 1);
	return (len);
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
	printf("Index de |%d|\n", format->index);
	printf("FORMAT____________________\n");
}

// t_fmt	*get_flags(char *s, int n, va_list ap)
// {
// 	int		i;
// 	int		next;
// 	int		j;
// 	t_fmt	*flags;
//
// 	j = 0;
// 	if (!(flags = ft_memalloc(sizeof(t_fmt) * n)) || !n)
// 		return (0);
// 	i = count_flags(s, 0)[0];
// 	i && display_string(s, 0, i);
// 	while (n-- > 0)
// 	{
// 		next = count_flags(s, i + 1)[0];
// 		get_options(ft_strsub(s, i,
// 			!n ? (int)ft_strlen(s) - i : next - i), &flags[j++], ap);
// 		i += (next - i);
// 	}
// 	return (flags);
// }
int			check_conversion(char **str)
{
	while (**str && !ft_strchr("diouxXcspfDOUbvr%", **str))
	{
		if (!ft_strchr("-+ #0lLhzj*.", **str) && !ft_isdigit(**str))
			return (0);
		(*str)++;
	}
	if (!(**str))
		return (0);
	(*str)++;
	return (1);
}
t_fmt	*get_options(char *str, va_list ap)
{
	//printf("str: {%s}\n", str);
	t_fmt *fmt;
	if (!(fmt = (t_fmt *)malloc(sizeof(t_fmt))))
		exit(1);
	fmt->length = get_length(str);
	fmt->field = get_field(str, ap);
	fmt->type = get_type(str);
	fmt->precision = get_precision(str, fmt, ap);
	fmt->prefixe = 0;
	fmt->opt = 0;
	fmt->signe = 0;
	while (*str && !~ft_indexof("diouxXcspfDOUbvr%", *str))
	{
		if (*str == '0' && !ft_isdigit(*(str - 1)) && *(str - 1) != '.')
			fmt->opt |= ZERO;
		if (*str == ' ' && !fmt->signe && (fmt->type >= F_ && fmt->type <= I_))
			fmt->signe = ' ';
		if (*str == '+' && (fmt->type >= F_ && fmt->type <= I_))
			fmt->signe = '+';
		if (*str == '#')
			fmt->opt |= HASH;
		if (*str == '-')
		{
			(fmt->opt |= SUB);
		}
		if (*str == '#' && (fmt->type== O_ || fmt->type== F_))
			fmt->prefixe = 1;
		if ((*str == '#' && (fmt->type== LOWX_ || fmt->type== HIGHX_)))
			fmt->prefixe = 2;
		str++;
	}
	if (fmt->type == LOWP_ || fmt->type == HIGHP_)
		fmt->prefixe = 2;
	return fmt;
}
int		parse(char *str, va_list ap)
{
	// int i = -1;
	// int length = 0;
	int j;
	// t_fmt *f;
	// int l = 0;
	// length = count_flags((char*)format, 0)[1];
	// f = get_flags((char*)format, length, ap);
	// j = count_flags((char*)format, 0)[0];
	// l += j ? splice((char*)format, j, 0) : 0;
	// if (!(count_flags((char*)format, 0)[0] + count_flags((char*)format, 0)[1]))
	// 	return (display_string((char*)format, 0, -1));
	// while (++i < length)
	// {
	// 	j = -1;
	// 	if (f[i].type == 1 << 30)
	// 		(void)f;
	// 	else
	// 	{
	// 		while (g_type[++j].type)
	// 		{
	// 			if (g_type[j].type == f[i].type)
	// 			{
	// 				l += g_type[j].function ? g_type[j].function(ap, &f[i]) : 0;
	// 				l += display_string(f[i].string, f[i].index, -1);
	// 				break ;
	// 			}
	// 		}
	// 	}
	// }
	t_fmt	*fmt;
	int			ret;

	ret = 0;
	while (*str)
	{
		j = -1;
		//printf("char: %c\n", *str);
		if (*str == '%')
		{
			fmt = get_options(++str, ap);
			if (check_conversion(&str))
			{
				while (g_type[++j].type)
				{
					if (g_type[j].type == fmt->type)
					{
						//display_fmt(fmt);
						ret += g_type[j].function ? g_type[j].function(ap, fmt) : 0;
						break ;
					}
				}
				free(fmt);
			}
		}
		else
		{
			//printf("lol\n");
			write(1, str++, 1);
			ret++;
		}
	}
	return (ret);
}

int		ft_printf(const char *format, ...)
{
	int		length;
	va_list	ap;
	va_start(ap, format);
	length = parse((char *)format, ap);
	va_end(ap);
	//printf("Longueur de %d\n", length);
	return (length);
}
