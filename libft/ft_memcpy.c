/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 13:24:25 by abutok            #+#    #+#             */
/*   Updated: 2017/10/26 13:41:55 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dstit;
	unsigned char	*srcit;
	size_t			i;

	dstit = (unsigned char*)dst;
	srcit = (unsigned char*)src;
	i = 0;
	while (i < n)
	{
		dstit[n - i - 1] = srcit[n - i - 1];
		i++;
	}
	return (dst);
}
