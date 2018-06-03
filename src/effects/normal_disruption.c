/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_disruption.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 12:50:43 by knovytsk          #+#    #+#             */
/*   Updated: 2018/05/11 12:50:44 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "effects.h"

unsigned int 	sin_gradient(t_sind *s, t_color color_t, int i)
{
	s->frequency[0] = 0.359;
 	s->frequency[1] = 0.160;
 	s->frequency[2] = 0.160;
	s->phase[0] = 0;
	s->phase[1] = 2;
	s->phase[2] = 4;

	color_t.spectrum.red = 200 * (sin(s->frequency[0] * i + s->phase[0]) * 127 + 128);
	color_t.spectrum.green = 200 * (sin(s->frequency[1] * i + s->phase[1]) * 127 + 128);
	color_t.spectrum.blue = 200 * (sin(s->frequency[2] * i + s->phase[2]) * 127 + 128);
	return (color_t.color);
}

unsigned int 	*normal_disruption(t_view *view)
{
	t_sind 			s;
  	int 			y;
	int 			x;

	s.center[X] = rand() % 500;
	s.center[Y] = rand() % 500;
	s.sin_texture = (unsigned int*)malloc(sizeof(unsigned int) * (500 * 500));
	y = -1;
	while (++y < 500)
	{
		x = -1;
		while (++x < 500)
		{
			s.color_t.color = 0xff;
			s.a = s.center[X] - x;
			s.b = s.center[Y] - y;
			s.distance = sqrt(s.a * s.a + s.b * s.b);
			s.sin_texture[y * 500 + x] = sin_gradient(&s, s.color_t, s.distance);
			// view->buff[y * WIDTH + x] = sin_gradient(&s, s.color_t, s.distance);
		}
	}
	return (s.sin_texture);
}
