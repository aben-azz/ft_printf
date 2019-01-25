/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 11:52:23 by aben-azz          #+#    #+#             */
/*   Updated: 2018/10/15 21:23:40 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		intlen(int n)
{
	int		len;

	if (n == -2147483648)
		return (11);
	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char			*ft_itoa(int n)
{
	char	*s;
	size_t	len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = intlen(n) + 1;
	if (!(s = (char*)malloc(sizeof(char) * len)))
		return (NULL);
	(n == 0) && (s[0] = '0');
	if (n < 0)
	{
		s[0] = '-';
		n = -n;
	}
	s[len - 1] = '\0';
	while (n)
	{
		len--;
		s[len - 1] = (n % 10) + '0';
		n /= 10;
	}
	return (s);
}
