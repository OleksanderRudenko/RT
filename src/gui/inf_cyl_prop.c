/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inf_cyl_prop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 15:37:32 by arudenko          #+#    #+#             */
/*   Updated: 2018/05/16 15:37:34 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#define NUM_CYL_PROP 8

// void	init_incyl_prop(t_view *s, t_icylinder *cyl, t_figure *fig)
// {
// 	t_col	c;

// 	s->prop.ic = (SDL_Texture **)malloc(sizeof(SDL_Texture*) * NUM_CYL_PROP);
// 	s->prop.ic_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect) * NUM_CYL_PROP);
// 	c = col_parse(fig->color);
// 	s->sl[0]->slider_rect.x = c.red;
// 	s->sl[0]->clr.red = s->sl[0]->slider_rect.x;
// 	s->sl[1]->slider_rect.x = c.green;
// 	s->sl[1]->clr.green = s->sl[1]->slider_rect.x;
// 	s->sl[2]->slider_rect.x = c.blue;
// 	s->sl[2]->clr.blue = s->sl[2]->slider_rect.x;
// 	s->prop.prop[0] =  create_text_ftoa(s, f->center.x , 2, 32);
// 	s->prop.prop[1] =  create_text_ftoa(s, f->center.y , 2, 32);
// 	s->prop.prop[2] =  create_text_ftoa(s, f->center.z , 2, 32);
// 	s->prop.prop[3] =  create_text_ftoa(s, f->radius , 2, 32);
// 	s->prop.prop[4] =  create_text_ftoa(s, fig->reflection , 2, 32);
// 	s->prop.prop[5] =  create_text_ftoa(s, c.red, 2, 32);
// 	s->prop.prop[6] =  create_text_ftoa(s, c.green, 2, 32);
// 	s->prop.prop[7] =  create_text_ftoa(s, c.blue, 2, 32);
// }