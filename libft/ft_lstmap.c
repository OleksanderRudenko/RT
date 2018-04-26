/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 16:01:20 by abutok            #+#    #+#             */
/*   Updated: 2017/11/01 12:21:44 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		del(void *mem, size_t content_size)
{
	free(mem);
	mem = NULL;
	content_size = 0;
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*nlst;
	t_list	*nlstiter;

	nlst = NULL;
	nlstiter = NULL;
	if (f == NULL || lst == NULL)
		return (NULL);
	nlst = f(lst);
	if (nlst == NULL)
		return (NULL);
	nlstiter = nlst;
	lst = lst->next;
	while (lst != NULL)
	{
		nlstiter->next = f(lst);
		if (nlstiter->next == NULL)
		{
			ft_lstdel(&nlst, &del);
			break ;
		}
		nlstiter = nlstiter->next;
		lst = lst->next;
	}
	return (nlst);
}
