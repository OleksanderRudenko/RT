/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 11:39:40 by abutok            #+#    #+#             */
/*   Updated: 2017/11/01 12:24:07 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char			*result;
	char			*resultit;
	unsigned int	i;

	result = NULL;
	if (s != NULL && f != NULL)
	{
		result = ft_strnew(ft_strlen(s));
		if (result == NULL)
			return (NULL);
		resultit = result;
		i = 0;
		while (*s)
			*resultit++ = f(i++, *s++);
	}
	return (result);
}
