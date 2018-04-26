/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 14:31:57 by abutok            #+#    #+#             */
/*   Updated: 2017/11/01 12:03:40 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dstit;
	unsigned char	*srcit;
	size_t			i;

	dstit = (unsigned char*)dst;
	srcit = (unsigned char*)src;
	i = 0;
	if (srcit < dstit)
		while (i < len)
		{
			dstit[len - i - 1] = srcit[len - i - 1];
			i++;
		}
	else
		while (i < len)
		{
			dstit[i] = srcit[i];
			i++;
		}
	return (dst);
}
