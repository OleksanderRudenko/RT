/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 10:29:27 by abutok            #+#    #+#             */
/*   Updated: 2017/11/24 18:27:44 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*s;
	size_t	i;

	s = (char*)malloc(size + 1);
	if (s == NULL)
		return (NULL);
	i = 0;
	while (i < size)
		s[i++] = '\0';
	s[i] = '\0';
	return (s);
}
