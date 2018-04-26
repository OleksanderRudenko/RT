/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 12:54:19 by abutok            #+#    #+#             */
/*   Updated: 2017/10/27 13:04:31 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*sit;
	char	ch;

	ch = (char)c;
	sit = (char*)s;
	while (*sit)
		sit++;
	while (sit >= s)
	{
		if (*sit == ch)
			return (sit);
		sit--;
	}
	return (NULL);
}
