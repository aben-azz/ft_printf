/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 08:43:37 by aben-azz          #+#    #+#             */
/*   Updated: 2019/02/27 08:48:42 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# define OPTIONS  "#0-+ "
# define TYPES    "cspPfFdDiIoOuUXxbvr%"
# define LENGTH   "lhLzj"
# define pf printf
# define HASH     1 << 0
# define ZERO     1 << 1
# define SUB      1 << 2
# define ADD      1 << 3
# define SPACE    1 << 4

# define L_      (1 << 1) + 1
# define LL_     (1 << 1)
# define H_      (1 << 2) + 1
# define HH_     (1 << 2)
# define LU_     (1 << 3) + 1
# define Z_      (1 << 4) + 1
# define J_      (1 << 5) + 1

typedef struct	s_fmt
{
	int				precision;
	int				length;
	int				type;
	int				field;
	int				opt;
	char			*string;
	int				index;
	int				signe;
	int				prefixe;
}				t_fmt;

typedef struct	s_ype
{
	int				type;
	int				(*function)(va_list list, t_fmt *fmt);
}				t_ype;
t_fmt			*get_flags(char *s, int n, va_list ap);
t_fmt			format(char *string);
int				ft_printf(const char *format, ...);
int				*count_flags(char *string, int index);
int				get_precision(char *string, t_fmt *fmt, va_list ap);
int				get_field(char *string, t_fmt *fmt, va_list ap);
int				get_length(char *s, char c);
char			get_type(char *str);
t_fmt			*get_options(char *str, va_list ap);
int				display_string(char *string, int index, int to);
void			view_fmt(t_fmt *flags, int length);
int				handle_char(va_list list, t_fmt *fmt);
int				handle_string(va_list list, t_fmt *fmt);
int				handle_array(va_list list, t_fmt *fmt);
int				handle_number(va_list ap, t_fmt *fmt);
void			display_fmt(t_fmt *fmt);
int				splice(char *string, int precision, int v);
int	intlen(long long len);
/*
	% -+0#espace	n				.n			h,hh,l,ll	(csp)diouXx
	  options		minimal_length  precision	length		type
	options
		+	signed ? add sign (+ || -) to output : NULL
		-	left align the field
		#	(type == oxX) ? add prefix to non-null output (0 || 0x || 0X)
		0	replace space with 0 in completition field
		" " replace the sign with an space
	minimal_length
		n;
	precision
		.n
	length
		hh		[diouXx]	(unsigned) char
		h		[diouXx]	short (unsigned) int
		ll		[diouXx]	(unsigned) long long int
		l		[diouXx]	(unsigned) long int
		l|L		[f]			long double
	type
		c	[no_length]		char
		s	[no_length]		string
		p	[no_length]		pointer
		f	[l|L]			float
		d	[hh|h|ll|l]		signed decimal integer
		i	[hh|h|ll|l]		signed decimal integer
		o	[hh|h|ll|l]		unsigned octal integer
		u	[hh|h|ll|l]		unsigned decimal integer
		X	[hh|h|ll|l]		unsigned hexadecimal integer uppercase
		x	[hh|h|ll|l]		unsigned hexadecimal integer lowercase
*/
#endif
