/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 10:21:29 by abutok            #+#    #+#             */
/*   Updated: 2017/11/02 12:37:50 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_lena(int n)
{
	size_t size;

	size = 0;
	if (n < 0)
	{
		size++;
		if (n < -2000000000)
		{
			size += ft_lena(n / -100000) + ft_lena(n % -100000);
			return (size);
		}
		n *= -1;
	}
	while (n >= 10)
	{
		n /= 10;
		size++;
	}
	size++;
	return (size);
}

static void		ft_filla(char **a, int n)
{
	char *ait;

	ait = *a;
	if (n < 0)
	{
		if (n < -2000000000)
		{
			ft_filla(a, n / (100000));
			ft_filla(a, n % 100000 * (-1));
			return ;
		}
		**a = '-';
		(*a)++;
		n *= -1;
	}
	if (n / 10 > 0)
		ft_filla(a, n / 10);
	**a = n % 10 + '0';
	(*a)++;
}

char			*ft_itoa(int n)
{
	char	*a;
	char	*a1;
	size_t	len;

	len = ft_lena(n);
	a = ft_strnew(len);
	if (a == NULL)
		return (NULL);
	a1 = a;
	ft_filla(&a1, n);
	return (a);
}
