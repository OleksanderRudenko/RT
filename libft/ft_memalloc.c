/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 10:09:15 by abutok            #+#    #+#             */
/*   Updated: 2017/10/28 10:14:41 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	unsigned char	*mem;
	size_t			i;

	mem = (unsigned char*)malloc(size);
	if (mem == NULL)
		return (NULL);
	i = 0;
	while (i < size)
		mem[i++] = 0;
	return (mem);
}
