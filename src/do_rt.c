/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_rt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 10:40:00 by abutok            #+#    #+#             */
/*   Updated: 2018/03/22 20:25:35 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		rt_lightr(t_vector l, t_vector normale,
		t_vector view, t_vector buf)
{
	t_vector	h;
	double		d;

	h = vsum(view, l);
	d = vscalar_multiple(h, normale);
	if (d > 0)
		return (buf.x * pow(d /
			vlen(h), buf.y));
	else
		return (0);
}

t_lrt		tlrt_init(t_space *space, t_ray *ray, t_figure *figure, double k)
{
	t_lrt	var;

	var.light = space->lights;
	var.intersection = get_intersection(ray, k);
	var.normale = get_normale(var.intersection, figure);
	if (vscalar_multiple(var.normale, ray->v) >= 0)
		var.normale = vk_multiple(var.normale, -1);
	var.bright = 0;
	var.reflected = 0;
	return (var);
}

/*
**	VERY VERY BAD CODE. HELLO NORMINETTE!
*/

int			do_lightrt(t_space *space, t_ray *ray, t_figure *figure, double k)
{
	t_lrt	v;

	v = tlrt_init(space, ray, figure, k);
	while (v.light != NULL)
	{
		if (v.light->type == LIGHT_TYPE_AMBIENT)
			v.bright += v.light->inten;
		else
		{
			v.vlight = vsub(v.light->o, v.intersection);
			v.buf = ray_init(v.intersection, v.vlight);
			if (!check_intersections(v.buf, space->figures))
			{
				if ((v.nl_s = vscalar_multiple(v.normale, v.vlight)) > 0)
					v.bright += v.light->inten * v.nl_s / vlen(v.vlight);
				if (v.nl_s > 0 && figure->reflection > 0)
					v.reflected += rt_lightr(v.vlight, v.normale,
							vk_multiple(ray->v, -1),
					vector_init(v.light->inten, figure->reflection, 0));
			}
			free(v.buf);
		}
		v.light = v.light->next;
	}
	return (set_brightness(figure->color, v.bright, v.reflected));
}

int			rt(t_space *space, t_ray *ray)
{
	t_figure	*iterator;
	t_figure	*closest;
	double		len;
	double		lbuf;

	len = INFINITY;
	iterator = space->figures;
	while (iterator != NULL)
	{
		lbuf = check_intersection(ray, iterator);
		if (lbuf >= 1.0 && lbuf < len)
		{
			len = lbuf;
			closest = iterator;
		}
		iterator = iterator->next;
	}
	if (len == INFINITY)
		return (0);
	else
		return (do_lightrt(space, ray, closest, len));
}

void		do_rt(t_view *view)
{
	t_ray		*ray;
	int			x;
	int			y;

	ray = ray_init(view->space->cam->o, (t_vector){0, 0, 1});
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			ray->v.x = (((x + 0.5) / WIDTH) * 2 - 1) * (((double)WIDTH) / HEIGHT) *
					tan(M_PI / 360 * FOV_X);
			ray->v.y = (1 - 2 * ((y + 0.5) / HEIGHT)) *
					tan(M_PI / 360 * FOV_Y);
			ray->v.z = 1;
			cam_rotate(ray, view->space->cam->v);
			view->buff[y * WIDTH + x] = rt(view->space, ray);
		}
	}
	// checkerboard_effect(view, 0);
	free(ray);
}
