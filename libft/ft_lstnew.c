/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 14:09:06 by abutok            #+#    #+#             */
/*   Updated: 2017/11/01 13:05:21 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list			*ft_lstnew(const void *content, size_t content_size)
{
	t_list			*elem;

	elem = (t_list*)malloc(sizeof(*elem));
	if (elem == NULL)
		return (NULL);
	elem->next = NULL;
	if (content == NULL)
	{
		elem->content = NULL;
		elem->content_size = 0;
	}
	else
	{
		elem->content = malloc(content_size);
		if (elem->content == NULL)
		{
			free(elem);
			return (NULL);
		}
		elem->content = ft_memcpy(elem->content, content, content_size);
		elem->content_size = content_size;
	}
	return (elem);
}
