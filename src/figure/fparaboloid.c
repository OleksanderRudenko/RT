/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fparaboloid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataranov <ataranov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 13:21:37 by ataranov          #+#    #+#             */
/*   Updated: 2018/06/10 13:25:11 by ataranov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_figure	*init_parab(t_figure *fparaboloid, t_vector v1, t_vector v2)
{
	fparaboloid = (t_figure*)ft_memalloc(sizeof(t_figure));
	fparaboloid->figure = (t_parabaloid*)ft_memalloc(sizeof(t_parabaloid));
	fparaboloid->type = Parabaloid;
	fparaboloid->next = NULL;
	((t_parabaloid*)fparaboloid->figure)->position = v1;
	((t_parabaloid*)fparaboloid->figure)->rotation = v2;
	return (fparaboloid);
}
