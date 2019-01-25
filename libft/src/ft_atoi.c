/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 15:24:52 by aben-azz          #+#    #+#             */
/*   Updated: 2018/11/14 11:00:04 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(char *str)
{
	int					signe;
	unsigned long long	result;

	result = 0;
	signe = 1;
	while (*str == '\n' || *str == '\t' || *str == '\r' || *str == '\v'
		|| *str == '\f' || *str == ' ')
		(void)*str++;
	(void)((*str == '-' || *str == '+') && (signe = *str++ == '-' ? -signe : signe));
	while (*str && ft_isdigit(*str))
	{
		if (result > 9223372036854775807)
			return (signe == -1 ? 0 : -1);
		result *= 10;
		result += *str++ - '0';
	}
	return ((int)(result * signe));
}
