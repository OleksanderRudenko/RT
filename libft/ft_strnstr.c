/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 13:37:41 by abutok            #+#    #+#             */
/*   Updated: 2017/10/27 14:23:20 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if ((!*haystack && !*needle) || !*needle)
		return ((char*)haystack);
	j = 0;
	while (*haystack && j < len)
	{
		if (*haystack == *needle)
		{
			i = 0;
			while (needle[i] && haystack[i] == needle[i])
				if ((i + j) == len)
					return (NULL);
				else
					i++;
			if (!needle[i])
				return ((char*)haystack);
		}
		haystack++;
		j++;
	}
	return (NULL);
}
