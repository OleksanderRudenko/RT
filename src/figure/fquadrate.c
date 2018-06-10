/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fquadrate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataranov <ataranov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 13:18:50 by ataranov          #+#    #+#             */
/*   Updated: 2018/06/10 13:25:41 by ataranov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_squard	*find_q_dots(t_squard *q)
{
	t_vector	tmp_x;
	t_vector	tmp_y;
	t_vector	tmp_z;

	tmp_x = (t_vector){0, 0, 0};
	tmp_y = vsum(tmp_x, vk_multiple(get_default_vector('y'), q->scale[0]));
	tmp_z = vsum(tmp_y, vk_multiple(get_default_vector('z'), q->scale[1]));
	q->points[0] = tmp_z;
	tmp_z = vsub(tmp_y, vk_multiple(get_default_vector('z'), q->scale[1]));
	q->points[1] = tmp_z;
	tmp_y = vsub(tmp_x, vk_multiple(get_default_vector('y'), q->scale[0]));
	tmp_z = vsum(tmp_y, vk_multiple(get_default_vector('z'), q->scale[1]));
	q->points[3] = tmp_z;
	tmp_z = vsub(tmp_y, vk_multiple(get_default_vector('z'), q->scale[1]));
	q->points[2] = tmp_z;
	return (q);
}

t_squard	*calc_quadrate_params(t_squard *q)
{
	int i;

	i = 0;
	q = find_q_dots(q);
	q->rotation = vk_multiple(q->rotation, 3.14f / 180);
	while (i < 4)
	{
		rotate_x(&q->points[i], q->rotation.x);
		rotate_y(&q->points[i], q->rotation.y);
		rotate_z(&q->points[i], q->rotation.z);
		q->points[i] = vsum(q->points[i], q->position);
		++i;
	}
	q->normale = count_triangle_normale(q->points);
	return (q);
}

t_figure	*quadrate_init(t_vector rotation, t_vector pos, double scale[2])
{
	t_figure *quadr;
	t_squard *q;

	quadr = (t_figure*)ft_memalloc(sizeof(t_figure));
	q = (t_squard*)ft_memalloc(sizeof(t_squard));
	q->rotation = rotation;
	q->position = pos;
	q->scale[0] = scale[0];
	q->scale[1] = scale[1];
	q = calc_quadrate_params(q);
	quadr->figure = q;
	quadr->type = Quadrate;
	quadr->next = NULL;
	return (quadr);
}
