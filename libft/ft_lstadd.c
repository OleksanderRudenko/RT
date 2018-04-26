/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 15:39:55 by abutok            #+#    #+#             */
/*   Updated: 2017/11/01 12:52:11 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd(t_list **alst, t_list *new)
{
	if (new == NULL || alst == NULL)
		return ;
	else if (*alst == NULL)
		*alst = new;
	else
	{
		new->next = *alst;
		*alst = new;
	}
	return ;
}
