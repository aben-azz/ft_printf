/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 23:46:55 by aben-azz          #+#    #+#             */
/*   Updated: 2019/02/05 23:50:13 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_utoa_base(unsigned long long nb, unsigned base, int uppercase)
{
	int					len;
	unsigned long long	tmp;
	char				*str;

	len = 1;
	tmp = nb;
	while (tmp >= base && ++len)
		tmp /= base;
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len] = '\0';
	tmp = "Aa"[uppercase];
	while (len-- && str[len] = n % b > 9 ? tmp + (n % b) : 48 + (n % b))
		nb /= base;
	return (str);
}
