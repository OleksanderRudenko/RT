/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 11:28:21 by abutok            #+#    #+#             */
/*   Updated: 2017/11/01 12:24:06 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(const char *s, char (*f)(char))
{
	char *result;
	char *resultit;

	result = NULL;
	if (s != NULL && f != NULL)
	{
		result = ft_strnew(ft_strlen(s));
		if (result == NULL)
			return (NULL);
		resultit = result;
		while (*s)
			*resultit++ = f(*s++);
	}
	return (result);
}
