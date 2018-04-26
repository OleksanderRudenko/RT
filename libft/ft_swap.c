/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 13:43:15 by abutok            #+#    #+#             */
/*   Updated: 2017/11/04 14:27:49 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap(void *v1, void *v2, size_t mem_size)
{
	unsigned char	ch;
	unsigned char	*m1;
	unsigned char	*m2;
	size_t			i;

	i = 0;
	if (v1 == NULL || v2 == NULL)
		return ;
	m1 = (unsigned char*)v1;
	m2 = (unsigned char*)v2;
	while (i < mem_size)
	{
		ch = m1[i];
		m1[i] = m2[i];
		m2[i++] = ch;
	}
}
