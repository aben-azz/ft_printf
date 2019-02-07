/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 18:48:05 by aben-azz          #+#    #+#             */
/*   Updated: 2019/02/07 19:48:20 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(intmax_t value, int base, int islower)
{
	int		i;
	char	*nbr;
	int		neg;

	i = 1;
	neg = 0;
	if (value < 0)
	{
		(base == 10) && (neg = 1);
		value *= -1;
	}
	while (ft_pow(base, i) - 1 < value)
		i++;
	nbr = (char*)malloc(sizeof(nbr) * i);
	nbr[i + neg] = '\0';
	while (i-- > 0)
	{
		nbr[i + neg] = (value % base) +
			(value % base > 9 ? "Aa"[islower] - 10 : '0');
		value = value / base;
	}
	(neg) && (nbr[0] = '-');
	return (nbr);
}
