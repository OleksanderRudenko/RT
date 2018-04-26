/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 14:51:49 by abutok            #+#    #+#             */
/*   Updated: 2017/11/01 14:25:38 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <libc.h>

static int	overflow_check(char *str, int sign)
{
	int i;

	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (i > 19)
		return (0);
	if (i == 19)
	{
		if (sign == 1 && ft_strncmp(str, "9223372036854775807", 19) > 0)
			return (0);
		else if (sign == -1 && ft_strncmp(str, "9223372036854775808", 19) > 0)
			return (0);
	}
	return (1);
}

int			ft_atoi(char *str)
{
	int sign;
	int val;

	while (*str == ' ' || ((*str >= 9) && (*str <= 13)))
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		sign = (*str == '-') ? -1 : 1;
		str++;
	}
	while (*str == '0')
		str++;
	if (overflow_check(str, sign))
	{
		val = 0;
		while (*str >= '0' && *str <= '9')
		{
			val *= 10;
			val += *str - '0';
			str++;
		}
		return (val * sign);
	}
	return (sign == 1 ? -1 : 0);
}
