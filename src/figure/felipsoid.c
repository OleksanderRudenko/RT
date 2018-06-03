/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   felipsoid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 13:28:12 by knovytsk          #+#    #+#             */
/*   Updated: 2018/05/08 13:28:13 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_figure  *elipsoid_init(t_vector position, t_vector rotation, int color, double reflection)
{
  t_figure *new_figure;
  t_elipsoid *elips;

  new_figure = (t_figure*)malloc(sizeof(t_figure));
	new_figure->type = Elipsoid;
  elips = (t_elipsoid*)malloc(sizeof(t_elipsoid));
	new_figure->figure = elips;
	elips->position = position;
  elips->rotation = vnormalize(rotation);
  elips->radius = 1;
  elips->rdistance = 1;
	new_figure->color = color;
	new_figure->reflection = reflection;
	new_figure->next = NULL;
	return (new_figure);
}
