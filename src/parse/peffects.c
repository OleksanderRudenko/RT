/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   peffects.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvinogra <vvinogra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 17:48:12 by knovytsk          #+#    #+#             */
/*   Updated: 2018/06/10 11:56:18 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_effects(t_view *view)
{
	view->space->antialiasing = 1;
	view->space->sepia = 0;
	view->space->inversion = 0;
	view->space->grayscale = 0;
	view->space->cartoon = 0;
}

void	parse_effects2(JSON_Object *effects, t_view *view)
{
	if (json_object_has_value_of_type(effects, "grayscale", JSONBoolean))
		view->space->grayscale = json_object_get_boolean(effects, "grayscale");
	if (json_object_has_value_of_type(effects, "cartoon", JSONBoolean))
		view->space->cartoon = json_object_get_boolean(effects, "cartoon");
}

void	parse_effects(JSON_Object *root, t_view *view)
{
	JSON_Object *effects;

	init_effects(view);
	if ((effects = json_object_get_object(root, "effects")) == NULL)
		return ;
	if (json_object_has_value_of_type(effects, "sepia", JSONBoolean))
		view->space->sepia = json_object_get_boolean(effects, "sepia");
	if (json_object_has_value_of_type(effects, "inversion", JSONBoolean))
		view->space->inversion = json_object_get_boolean(effects, "inversion");
	if (json_object_has_value_of_type(effects, "antialiasing", JSONNumber))
		view->space->antialiasing = json_object_get_number(effects,
														"antialiasing");
	if (view->space->antialiasing > 4 || view->space->antialiasing < 1)
		view->space->antialiasing = 1;
	parse_effects2(effects, view);
}
