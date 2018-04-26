/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 14:48:32 by abutok            #+#    #+#             */
/*   Updated: 2017/10/28 15:19:13 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s)
{
	unsigned long	start;
	size_t			size;

	if (s == NULL)
		return (NULL);
	if (*s == '\0')
		return (ft_strnew(0));
	start = 0;
	while ((s[start] == ' ' || s[start] == '\n' || s[start] == '\t')
		&& s[start] != '\0')
		start++;
	size = ft_strlen(s);
	if (start == size)
		return (ft_strnew(0));
	while (s[size] == ' ' || s[size] == '\n' || s[size] == '\t'
		|| s[size] == '\0')
		size--;
	return (ft_strsub(s, start, (size - start + 1)));
}
