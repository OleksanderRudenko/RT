/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 14:05:53 by knovytsk          #+#    #+#             */
/*   Updated: 2018/04/17 14:49:48 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parse_cam(JSON_Object *root, t_view *view)
{
	JSON_Object *cam;

	cam = json_object_get_object(root, "cam");
	if (cam == NULL)
		return ;
	view->space->cam = ray_init((t_vector){0, 0, 0}, (t_vector){0, 0, 0});
	if (json_object_has_value_of_type(cam, "position", JSONArray))
		view->space->cam->o = parse_vector(json_object_get_array(cam,
				"position"), view->space->cam->o);
	else
		ft_putendl_fd("Unknown cam position. Default applied", STDERR_FILENO);
	if (json_object_has_value_of_type(cam, "rotation", JSONArray))
		view->space->cam->v = parse_vector(json_object_get_array(cam,
				"rotation"), view->space->cam->v);
	else
		ft_putendl_fd("Unknown cam rotation. Default applied", STDERR_FILENO);
}
