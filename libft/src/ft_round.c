/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 00:50:21 by aben-azz          #+#    #+#             */
/*   Updated: 2019/02/06 03:20:14 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

long double	ft_round(long double fl, long precision)
{
	long double	diviseur;

	diviseur = 0.;
	if (!precision)
		return (fl + (fl > 0.0 ? 0.5 : -0.5));
	while (--precision >= 0)
		diviseur /= 10;
	return (fl + (fl > 0.0 ? diviseur : -diviseur));
}
