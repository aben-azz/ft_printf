/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 08:43:19 by aben-azz          #+#    #+#             */
/*   Updated: 2019/02/27 08:50:21 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include "ft_printf.h"

t_ype g_type[] = {
	{'c', &handle_char},
	{'%', &handle_char},
	{'s', &handle_string},
	{'p', &handle_number},
	{'P', &handle_number},
	{'f', &handle_number},
	{'F', &handle_number},
	{'d', &handle_number},
	{'D', &handle_number},
	{'i', &handle_number},
	{'I', &handle_number},
	{'o', &handle_number},
	{'O', &handle_number},
	{'u', &handle_number},
	{'U', &handle_number},
	{'X', &handle_number},
	{'x', &handle_number},
	{'b', &handle_number},
	{'B', &handle_number},
	{'v', &handle_array},
	{'r', &handle_array}
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
	//printf("type: %c\n", fmt->type);
	if (fmt->length == L_ || fmt->length == LL_ || ~ft_indexof("pP", fmt->type))
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
	char *temp;

	temp = NULL;
	uppercase = 0;
	b = 10;
	(~ft_indexof("xXpP", fmt->type)) && (b = 16);
	(~ft_indexof("XP", fmt->type)) && (uppercase = 1);
	(~ft_indexof("oO", fmt->type)) && (b = 8);
	(~ft_indexof("bB", fmt->type)) && (b = 2);
	if (fmt->type == 'f')
	{
		if (fmt->length == LU_)
			str = ft_ftoa(va_arg(ap, long double),
				!~fmt->precision ? 6 : fmt->precision);
		else
			str = ft_ftoa(va_arg(ap, double),
				!~fmt->precision ? 6 : fmt->precision);
		if (str && fmt->prefixe && !ft_strchr(str, '.') && (temp = str))
			str = ft_strjoin(str, ".");
		ft_strdel(&temp);
	}
	else
	{
		if (~ft_indexof("di", fmt->type))
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

	if (fmt->type == 'c')
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
	c = (~ft_indexof("pP", c)) ? "xX"[c == 'P'] : c;
	if (~ft_indexof("oOxX", c))
	{
		ft_putchar('0');
		i++;
	}
	if (~ft_indexof("xX", c))
	{
		ft_putchar("Xx"[c == 'x']);
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

	(!~ft_indexof("fF", fmt->type) && ~fmt->precision) && (fmt->opt &= ~(ZERO));
	str = get_s(fmt, ap);
	if (!fmt->precision && str[0] == '0' && !~ft_indexof("fF", fmt->type))
	{
		if (~ft_indexof("Xx", fmt->type))
			fmt->prefixe = 0;
		str[0] = '\0';
	}
	if (!~ft_indexof("Pp", fmt->type))
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

	if (fmt->type == 'v')
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
		fmt->type == 'v' ? ft_putnbr(array[i++]) : ft_putstr(string[i++]);
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
	while (*str && !~ft_indexof(TYPES, *str))
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
	if (!point && ~ft_indexof("fF", fmt->type))
		precision = 6;
	return (precision);
}

int		get_field(char *str, t_fmt *fmt, va_list ap)
{
	int width;
	int temp;

	width = 0;
	while (*str && !~ft_indexof(TYPES, *str))
	{
		if (*str == '.' && str++)
		{
			while (ft_isdigit(*str))
				str++;
			str += (*str == '*' && *(str - 1) == '.');
			continue;
		}
		(*str == '*') && (width = va_arg(ap, int));
		(*str == '*' && width < 0) && (fmt->opt |= SUB);
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

int		get_length(char *s, char c)
{
	//printf("{%s}\n", s);
	int n;
	int i;

	i = 0;
	n = 0;
	while (!~ft_indexof(LENGTH, s[n++]) && s[n] && n < ft_indexof(s, c))
		(void)i++;
	if (~(n = ft_indexof(LENGTH, s[i])))
		return (ft_count(s, s[i]) ? (1 << (n)) + (ft_count(s, s[i]) % 2) : -1);
	else
		return (-1);
}

char		get_type(char *str)
{
	int i;

	i = 0;
	while (!~ft_indexof(TYPES, str[i]))
		i++;
	//return (1 << (ft_indexof(TYPES, str[i]) - 1));
	return (str[i]);
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
	'c' == format->type && printf("C\n");
	's' == format->type && printf("S\n");
	'p' == format->type && printf("p\n");
	'P' == format->type && printf("P\n");
	'f' == format->type && printf("F\n");
	'd' == format->type && printf("D\n");
	'i' == format->type && printf("I\n");
	'u' == format->type && printf("U\n");
	'X' == format->type && printf("X\n");
	'o' == format->type && printf("O\n");
	'x' == format->type && printf("x\n");
	printf("format de %d\n", format->opt);
	(format->opt & HASH) && printf("#\n");
	(format->opt & SUB) && printf("-\n");
	(format->opt & ZERO) && printf("0\n");
	(format->opt & ADD) && printf("+\n");
	(format->opt & SPACE) && printf("SPACE\n");
	printf("Precision de |%d|\n", format->precision);
	printf("Champs de |%d|\n", format->field);
	printf("FORMAT____________________\n");
}

int			check_conversion(char **str)
{
	while (**str && !~ft_indexof(TYPES, **str))
	{
		if (!~ft_indexof("-+ #0lLhzj*.", **str) && !ft_isdigit(**str))
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
	fmt->opt = 0;

	fmt->field = get_field(str, fmt, ap);
	fmt->type = get_type(str);
	fmt->length = get_length(str, fmt->type);
	if (~ft_indexof("DOUF", fmt->type))
	{
		fmt->length = L_;
		fmt->type = ft_tolower(fmt->type);
	}
	fmt->precision = get_precision(str, fmt, ap);
	fmt->prefixe = 0;
	fmt->signe = 0;
	while (*str && !~ft_indexof(TYPES, *str))
	{
		if (*str == '0' && !ft_isdigit(*(str - 1)) && *(str - 1) != '.')
			fmt->opt |= ZERO;
		if (*str == ' ' && !fmt->signe && (~ft_indexof("FfiIdD", fmt->type)))
			fmt->signe = ' ';
		if (*str == '+' && (~ft_indexof("fFiIdD", fmt->type)))
			fmt->signe = '+';
		if (*str == '#')
			fmt->opt |= HASH;
		if (*str == '-')
		{
			(fmt->opt |= SUB);
		}
		if (*str == '#' && (~ft_indexof("oOfF", fmt->type)))
			fmt->prefixe = 1;
		if ((*str == '#' && (~ft_indexof("xX", fmt->type))))
			fmt->prefixe = 2;
		str++;
	}
	if (~ft_indexof("pP", fmt->type))
		fmt->prefixe = 2;

	return fmt;
}
int		parse(char *str, va_list ap)
{
	int j;
	t_fmt	*fmt;
	int			ret;

	ret = 0;
	while (*str)
	{
		j = -1;
		if (*str == '%')
		{
			fmt = get_options(++str, ap);
			if (check_conversion(&str))
			{
				while (g_type[++j].type)
				{
					if (g_type[j].type == fmt->type)
					{
						ret += g_type[j].function ? g_type[j].function(ap, fmt) : 0;
						break ;
					}
				}
				free(fmt);
			}
		}
		else
		{
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
