/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 15:27:51 by abutok            #+#    #+#             */
/*   Updated: 2017/10/30 12:25:39 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list *lstnext;

	if (alst == NULL || *alst == NULL || del == NULL)
		return ;
	lstnext = (*alst)->next;
	ft_lstdelone(alst, del);
	ft_lstdel(&lstnext, del);
}
