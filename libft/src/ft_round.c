/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 00:50:21 by aben-azz          #+#    #+#             */
/*   Updated: 2019/01/30 00:52:44 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long double	ft_round(long double fl, long precision)
{
	long double	diviseur;

	diviseur = 0.05;
	while (precision-- >= 0)
		diviseur /= 10;
	return (fl + (fl > 0.0 ? diviseur : -diviseur));
}
