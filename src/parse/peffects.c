/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   peffects.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 17:48:12 by knovytsk          #+#    #+#             */
/*   Updated: 2018/05/16 17:48:13 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void 	init_effects(t_view *view)
{
	view->space->antialiasing = 0;
	view->space->sepia = 0;
}

void 	parse_effects(JSON_Object *root, t_view *view)
{
	JSON_Object *effects;

	if ((effects = json_object_get_object(root, "effects")) == NULL)
		return ;
	init_effects(view);
	if (json_object_has_value_of_type(effects, "sepia", JSONNumber))
		view->space->sepia = json_object_get_number(effects, "sepia");
	else
		ft_putendl_fd("Invalid effect parameter. Default applied",
						STDERR_FILENO);
	if (json_object_has_value_of_type(effects, "sepia", JSONNumber))
		view->space->antialiasing = json_object_get_number(effects, "antialiasing");
	else
		ft_putendl_fd("Invalid effect parameter. Default applied",
						STDERR_FILENO);

}
