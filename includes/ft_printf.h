/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 08:43:37 by aben-azz          #+#    #+#             */
/*   Updated: 2019/02/27 11:03:12 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "../libft/includes/libft.h"
# define TYPES    "cspPfFdDiIoOuUXxbvr%"
# define LENGTH   "lhLzj"
# define HASH    (1 << 0)
# define ZERO    (1 << 1)
# define SUB     (1 << 2)

typedef struct	s_fmt
{
	int				prec;
	int				length;
	int				type;
	int				field;
	int				opt;
	int				signe;
	int				prefixe;
}				t_fmt;
typedef struct	s_ype
{
	int				type;
	int				(*function)(va_list list, t_fmt *fmt);
}				t_ype;
int				handle_char(va_list list, t_fmt *fmt);
int				handle_string(va_list list, t_fmt *fmt);
int				handle_array(va_list list, t_fmt *fmt);
int				print_numbers(t_fmt *fmt, char *str, int len);
int				handle_number(va_list ap, t_fmt *fmt);
t_fmt			*get_options(char *s, va_list ap);
char			*get_s(t_fmt *fmt, va_list ap);
int				ft_printf(const char *format, ...);
#endif
