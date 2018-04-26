/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 13:15:17 by abutok            #+#    #+#             */
/*   Updated: 2017/10/27 14:17:06 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;

	if (!*haystack && !*needle)
		return ((char*)haystack);
	if (!*needle)
		return ((char*)haystack);
	while (*haystack)
	{
		if (*haystack == *needle)
		{
			i = 0;
			while (needle[i] && haystack[i] == needle[i])
				i++;
			if (!needle[i])
				return ((char*)haystack);
		}
		haystack++;
	}
	return (NULL);
}
