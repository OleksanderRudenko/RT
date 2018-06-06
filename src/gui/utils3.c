/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 19:17:58 by arudenko          #+#    #+#             */
/*   Updated: 2018/06/06 19:18:00 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char	*light_type(char num)
{
	if (num == 0)
		return ("AMBIENT");
	else if (num == 1)
		return ("POINT");
	return ("DIRECTIONAL");
}

// int			rt_figure(t_view *s, int x, int y)
// {
// 	t_figure	*iterator;
// 	double		len;
// 	double		lbuf;
// 	t_ray		*ray;
// 	int			i;
// 	int			a = 0;

// 	ray = ray_init(s->space->cam->o, (t_vector){0, 0, 1});
// 	ray->v.x = (((x + 0.5) / WIDTH) * 2 - 1) * (((double)WIDTH) / HEIGHT) *
// 					tan(M_PI / 360 * FOV_X);
// 	ray->v.y = (1 - 2 * ((y + 0.5) / HEIGHT)) *
// 			tan(M_PI / 360 * FOV_Y);
// 	ray->v.z = 1;
// 	cam_rotate(ray, s->space->cam->v);
// 	len = INFINITY;
// 	iterator = s->space->figures;
// 	i = 0;
// 	while (iterator != NULL)
// 	{
// 		lbuf = check_intersection(ray, iterator);
// 		if (lbuf >= 1.0 && lbuf < len)
// 		{
// 			len = lbuf;
// 			a = i;
// 		}
// 		iterator = iterator->next;
// 		i++;
// 	}
// 	free(ray);
// 	if (len == INFINITY)
// 		return (-1);
// 	return (a);
// }
