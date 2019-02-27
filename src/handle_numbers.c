/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_numbers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 09:23:45 by aben-azz          #+#    #+#             */
/*   Updated: 2019/02/27 09:50:16 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int			print_prefixe(int c)
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

static intmax_t		get_signed(t_fmt *fmt, va_list ap)
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

static uintmax_t	get_unsigned(t_fmt *fmt, va_list ap)
{
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

int					print_numbers(t_fmt *fmt, char *str, int len)
{
	int ret;

	ret = 0;
	if (fmt->opt & SUB)
	{
		fmt->signe ? ft_putchar(fmt->signe) : NULL;
		if (fmt->prefixe)
			ret = print_prefixe(fmt->type);
		ft_repeat_char('0', fmt->prec);
		ft_putstr(str);
		ft_repeat_char(' ', len);
	}
	else
	{
		(~fmt->opt & ZERO) && ft_repeat_char(' ', len);
		fmt->signe ? ft_putchar(fmt->signe) : NULL;
		if (fmt->prefixe)
			ret = print_prefixe(fmt->type);
		(fmt->opt & ZERO) && ft_repeat_char('0', len);
		ft_repeat_char('0', fmt->prec);
		ft_putstr(str);
	}
	len = len < 0 ? 0 : len;
	return (ret + ft_strlen(str) + len + fmt->prec + (fmt->signe != 0));
}

char				*get_s(t_fmt *fmt, va_list ap)
{
	char	*str;
	char	b;
	char	uppercase;
	char	*temp;

	temp = NULL;
	uppercase = 0;
	b = 10;
	(~ft_indexof("xXpP", fmt->type)) && (b = 16);
	(~ft_indexof("XP", fmt->type)) && (uppercase = 1);
	(~ft_indexof("oO", fmt->type)) && (b = 8);
	(~ft_indexof("bB", fmt->type)) && (b = 2);
	if (fmt->type == 'f')
	{
		str = (fmt->length == LU_) ? ft_ftoa(va_arg(ap, long double),
		fmt->prec) : ft_ftoa(va_arg(ap, double), fmt->prec);
		if (str && fmt->prefixe && !~ft_indexof(str, '.') && (temp = str))
			str = ft_strjoin(str, ".");
		ft_strdel(&temp);
	}
	else
		str = (~ft_indexof("di", fmt->type)) ? ft_itoa_base(get_signed(fmt, ap),
			b, uppercase) : ft_utoa_base(get_unsigned(fmt, ap), b, uppercase);
	!str ? exit(0) : NULL;
	return (str);
}
