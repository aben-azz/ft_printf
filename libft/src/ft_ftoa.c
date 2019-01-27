/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 08:00:33 by aben-azz          #+#    #+#             */
/*   Updated: 2019/01/27 08:38:39 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_ftoa(double f, int precision, char *str)
{
	int a;
	int b;
	int k;

	(f < 0.0) && (*str++ = '-');
	(f < 0.0) && (f *= -1);
	a = f;
	f -= a;
	k = precision;
	while (k-- > -1)
		if (a / ft_pow(10, k) > 0)
			break ;
	k++;
	while (k > 0 && (*str++ = a / ft_pow(10, k - 1) + 48))
		a %= ft_pow(10, k-- - 1);
	*str++ = '.';
	while (precision-- > 0 && (f *= 10.0) && (b = f))
	{
		(*str++ = b + 48);
		f -= b;
	}
	*str = '\0';
}
