/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elipsooid_prop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 14:29:01 by arudenko          #+#    #+#             */
/*   Updated: 2018/05/21 14:29:03 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static inline void	elips_prop2(t_view *s)
{
	s->elp.el_rect[4] = make_rect(10, 400, 100, 32);
	s->elp.el_tex[4] = create_text(s, "Reflection", 2, 32);
	s->elp.el_pr_rect[4] = make_rect(120, 400, 60, 32);
	s->elp.el_prop[4] =  tf(s, 0, 2, 32);
	s->elp.el_rect[5] = make_rect(10, 450, 100, 32);
	s->elp.el_tex[5] = create_text(s, "Rotation-X", 2, 32);
	s->elp.el_pr_rect[5] = make_rect(120, 450, 60, 32);
	s->elp.el_prop[5] =  tf(s, 0, 2, 32);
	s->elp.el_rect[6] = make_rect(10, 500, 100, 32);
	s->elp.el_tex[6] = create_text(s, "Rotation-Y", 2, 32);
	s->elp.el_pr_rect[6] = make_rect(120, 500, 60, 32);
	s->elp.el_prop[6] =  tf(s, 0, 2, 32);
	s->elp.el_rect[7] = make_rect(10, 550, 100, 32);
	s->elp.el_tex[7] = create_text(s, "Rotation-Z", 2, 32);
	s->elp.el_pr_rect[7] = make_rect(120, 550, 60, 32);
	s->elp.el_prop[7] =  tf(s, 0, 2, 32);
	s->elp.el_rect[8] = make_rect(10, 600, 100, 32);
	s->elp.el_tex[8] = create_text(s, "Rdistance", 2, 32);
	s->elp.el_pr_rect[8] = make_rect(120, 600, 60, 32);
	s->elp.el_prop[8] =  tf(s, 0, 2, 32);
}

void	elips_prop(t_view *s)
{
	s->elp.el_tex = (SDL_Texture **)malloc(sizeof(SDL_Texture*) * NUM_EL_PR);
	s->elp.el_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect) * NUM_EL_PR);
	s->elp.el_pr_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect) * NUM_EL_PR);
	s->elp.el_prop = (SDL_Texture **)malloc(sizeof(SDL_Texture*) * NUM_EL_PR);
	s->elp.el_rect[0] = make_rect(10, 200, 100, 32);
	s->elp.el_tex[0] = create_text(s, "Position-X", 2, 32);
	s->elp.el_pr_rect[0] = make_rect(120, 200, 60, 32);
	s->elp.el_prop[0] =  tf(s, 0, 2, 32);
	s->elp.el_rect[1] = make_rect(10, 250, 100, 32);
	s->elp.el_tex[1] = create_text(s, "Position-Y", 2, 32);
	s->elp.el_pr_rect[1] = make_rect(120, 250, 60, 32);
	s->elp.el_prop[1] =  tf(s, 0, 2, 32);
	s->elp.el_rect[2] = make_rect(10, 300, 100, 32);
	s->elp.el_tex[2] = create_text(s, "Position-Z", 2, 32);
	s->elp.el_pr_rect[2] = make_rect(120, 300, 60, 32);
	s->elp.el_prop[2] =  tf(s, 0, 2, 32);
	s->elp.el_rect[3] = make_rect(10, 350, 100, 32);
	s->elp.el_tex[3] = create_text(s, "Radius", 2, 32);
	s->elp.el_pr_rect[3] = make_rect(120, 350, 60, 32);
	s->elp.el_prop[3] =  tf(s, 0, 2, 32);
	elips_prop2(s);
}

void	init_elips_prop(t_view *s)
{
	t_col	c;

	c = col_parse(s->space->cl_figures[s->rr.fl.y].color);
	s->sl[0]->slider_rect.x = c.red;
	s->sl[0]->clr.red = s->sl[0]->slider_rect.x;
	s->sl[1]->slider_rect.x = c.green;
	s->sl[1]->clr.green = s->sl[1]->slider_rect.x;
	s->sl[2]->slider_rect.x = c.blue;
	s->sl[2]->clr.blue = s->sl[2]->slider_rect.x;
	s->elp.el_prop[0] = tf(s, s->space->cl_figures[s->rr.fl.y].position.x, 2, 32);
	s->elp.el_prop[1] = tf(s, s->space->cl_figures[s->rr.fl.y].position.y, 2, 32);
	s->elp.el_prop[2] = tf(s, s->space->cl_figures[s->rr.fl.y].position.z, 2, 32);
	s->elp.el_prop[3] = tf(s, s->space->cl_figures[s->rr.fl.y].radius, 2, 32);
	s->elp.el_prop[4] = tf(s, s->space->cl_figures[s->rr.fl.y].reflection, 2, 32);
	s->elp.el_prop[5] = tf(s, s->space->cl_figures[s->rr.fl.y].rotation.x, 2, 32);
	s->elp.el_prop[5] = tf(s, s->space->cl_figures[s->rr.fl.y].rotation.y, 2, 32);
	s->elp.el_prop[7] = tf(s, s->space->cl_figures[s->rr.fl.y].rotation.z, 2, 32);
	s->elp.el_prop[8] = tf(s, s->space->cl_figures[s->rr.fl.y].rdistance, 2, 32);
}

void	print_elips_prop(t_view *s)
{
	int i;

	i = 0;
	SDL_RenderClear(s->rr.rend[2]);
	while (i < NUM_EL_PR && s->flag == 0)
	{
		SDL_RenderCopy(s->rr.rend[2], s->elp.el_tex[i], NULL, &s->elp.el_rect[i]);
		SDL_RenderCopy(s->rr.rend[2], s->elp.el_prop[i], NULL, &s->elp.el_pr_rect[i]);
		SDL_RenderCopy(s->rr.rend[2], s->ok->b_ok, NULL, &s->ok->ok_rect);
		display_colored_rect(s);
		i++;
	}
	SDL_RenderPresent(s->rr.rend[2]);
}

void	clean_elips_prop(t_view *s)
{
	int	i;

	i = -1;
	while (++i < NUM_EL_PR)
	{
		if (s->elp.el_tex[i])
		{
			SDL_DestroyTexture(s->elp.el_tex[i]);
			s->elp.el_tex[i] = NULL;
		}
		if (s->elp.el_prop[i])
		{
			SDL_DestroyTexture(s->elp.el_prop[i]);
			s->elp.el_prop[i] = NULL;
		}
	}
}
