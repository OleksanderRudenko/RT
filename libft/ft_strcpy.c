/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 12:19:32 by abutok            #+#    #+#             */
/*   Updated: 2017/10/27 12:00:35 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(src) + 1;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}
