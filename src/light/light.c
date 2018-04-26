/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 19:02:00 by abutok            #+#    #+#             */
/*   Updated: 2018/03/16 19:02:00 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_light		*light_init(char type, t_vector o, double inten)
{
	t_light *new_light;

	new_light = (t_light*)malloc(sizeof(t_light));
	new_light->type = type;
	new_light->o = o;
	new_light->inten = inten;
	new_light->next = NULL;
	return (new_light);
}
