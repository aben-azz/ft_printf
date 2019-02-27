/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 09:27:44 by aben-azz          #+#    #+#             */
/*   Updated: 2019/02/27 09:50:33 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	splice(char *string, int prec, int v)
{
	char *l;

	l = ft_strsub(string, 0, ~prec ? prec : ft_strlen(string));
	v ? ft_putstr(l) : NULL;
	return ((int)ft_strlen(l));
}

int			handle_char(va_list list, t_fmt *fmt)
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

int			handle_string(va_list list, t_fmt *fmt)
{
	int		l;
	char	*string;

	l = 0;
	string = va_arg(list, char*);
	string = !string ? "(null)" : string;
	fmt->opt & SUB ? splice(string, fmt->prec, 1) : 0;
	l += ft_repeat_char(fmt->opt & ZERO && (~fmt->opt & SUB) ? '0' : ' ',
		fmt->field - splice(string, fmt->prec, 0));
	l = ft_max(l, 0);
	!(fmt->opt & SUB) ? splice(string, fmt->prec, 1) : 0;
	return (l + splice(string, fmt->prec, 0));
}

int			handle_array(va_list list, t_fmt *fmt)
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

int			handle_number(va_list ap, t_fmt *fmt)
{
	char		*str;
	int			len;

	(!~ft_indexof("fF", fmt->type) && ~fmt->prec) && (fmt->opt &= ~(ZERO));
	(~ft_indexof("fF", fmt->type)) && (fmt->prec = !~fmt->prec ? 6 : fmt->prec);
	str = get_s(fmt, ap);
	if (!fmt->prec && str[0] == '0' && !~ft_indexof("fF", fmt->type))
	{
		if (~ft_indexof("Xx", fmt->type))
			fmt->prefixe = 0;
		str[0] = '\0';
	}
	if (!~ft_indexof("Pp", fmt->type))
		fmt->prefixe = *str == '0' ? 0 : fmt->prefixe;
	if (*str == '-')
		fmt->signe = *(str++);
	fmt->prec -= ft_strlen(str);
	fmt->prec = fmt->prefixe == 1 ? fmt->prec - 1 : fmt->prec;
	fmt->prec = fmt->prec < 0 ? 0 : fmt->prec;
	len = fmt->field - ft_strlen(str) - (fmt->signe ? 1 : 0) - fmt->prec;
	len -= fmt->prefixe;
	len = print_numbers(fmt, str, len);
	fmt->signe == '-' ? free(--str) : ft_strdel(&str);
	return (len);
}
