/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 14:18:48 by abutok            #+#    #+#             */
/*   Updated: 2017/10/28 14:46:58 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*r;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL)
		r = ft_strnew(ft_strlen(s2));
	else if (s2 == NULL)
		r = ft_strnew(ft_strlen(s1));
	else
		r = ft_strnew(ft_strlen(s2) + ft_strlen(s1));
	if (r == NULL)
		return (NULL);
	if (s1 != NULL)
		ft_strcat(r, s1);
	if (s2 != NULL)
		ft_strcat(r, s2);
	return (r);
}
