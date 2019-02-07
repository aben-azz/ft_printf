/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 08:00:33 by aben-azz          #+#    #+#             */
/*   Updated: 2019/02/07 22:29:55 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_ftoa(long double f, int precision, char *str)
{

	long long a;
	long long b;
	long long k;

	(f < 0.0) && (f *= -1);
	f = ft_round(f, precision);
	a = f;
	k = ft_intlen((int)f);
	f -= a;
	while (k > 0 && (*str++ = a / ft_pow(10, k - 1) + 48))
		a %= ft_pow(10, k-- - 1);
	precision <= 0 || (*str++ = '.');
	while (precision-- > 0)
	{
		f *= 10.0;
		b = f;
		*str++ = b + 48;
		f -= b;
	}
	*str = '\0';
}
