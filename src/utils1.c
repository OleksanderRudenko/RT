/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 18:30:21 by arudenko          #+#    #+#             */
/*   Updated: 2018/05/01 18:30:23 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	num_figures(t_view *s)
{
	int			i;
	t_figure	*fig;

	fig = s->space->figures;
	i = 0;
	if (fig == NULL)
		return (0);
	while (fig)
	{
		i++;
		fig = fig->next; 
	}
	return (i);
}

char	*figure_type(t_figure_type num)
{
	if (num == 0)
		return ("InfinitePlane");
	else if (num == 1)
		return ("Sphere");
	else if (num == 2)
		return ("InfiniteCylinder");
	else if (num == 3)
		return("InfiniteCylinder");
	else if (num == 4)
		return ("Triangle");
	else if (num == 5)
		return ("Cube");
	return ("LOL WAT");
}
