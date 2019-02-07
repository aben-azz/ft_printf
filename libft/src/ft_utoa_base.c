/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 23:46:55 by aben-azz          #+#    #+#             */
/*   Updated: 2019/02/07 22:00:56 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(uintmax_t nbr, int base)
{
	int digits;

	digits = 0;
	while (nbr)
	{
		digits++;
		nbr /= base;
	}
	return (digits);
}


char		*ft_utoa_base(uintmax_t nb, int base, int uppercase)
{
	char	*output;
	int		digits;

	if (nb == 0)
		return (ft_strdup("0"));
	digits = count_digits(nb, base);
	output = ft_strnew(digits);
	while (digits--)
	{
		output[digits] = (nb % base) +
			(nb % base > 9 ? "aA"[uppercase] - 10 : '0');
		nb /= base;
	}
	return (output);
}
