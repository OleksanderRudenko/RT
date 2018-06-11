/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parabaloid_prop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 14:29:51 by arudenko          #+#    #+#             */
/*   Updated: 2018/05/21 14:29:52 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static inline void	parab_prop2(t_view *s)
{
	s->par.pr_rect[4] = make_rect(10, 400, 100, 32);
	s->par.pr_tex[4] = create_text(s, "Reflection", 2, 32);
	s->par.pr_pr_rect[4] = make_rect(120, 400, 60, 32);
	s->par.pr_prop[4] = tf(s, 0, 2, 32);
	s->par.pr_rect[5] = make_rect(80, 450, 80, 32);
	s->par.pr_tex[5] = create_text(s, "Rotate-X", 2, 32);
	s->par.pr_pr_rect[5] = make_rect(120, 450, 60, 32);
	s->par.pr_prop[5] = NULL;
	s->par.pr_rect[6] = make_rect(80, 500, 80, 32);
	s->par.pr_tex[6] = create_text(s, "Rotate-Y", 2, 32);
	s->par.pr_pr_rect[6] = make_rect(120, 500, 60, 32);
	s->par.pr_prop[6] = NULL;
	s->par.pr_rect[7] = make_rect(80, 550, 80, 32);
	s->par.pr_tex[7] = create_text(s, "Rotate-Z", 2, 32);
	s->par.pr_pr_rect[7] = make_rect(120, 550, 60, 32);
	s->par.pr_prop[7] = NULL;
	s->par.pr_rect[8] = make_rect(10, 600, 60, 32);
	s->par.pr_tex[8] = create_text(s, "Mirror", 2, 32);
	s->par.pr_pr_rect[8] = make_rect(120, 600, 60, 32);
	s->par.pr_prop[8] = tf(s, 0, 2, 32);
	s->par.pr_rect[9] = make_rect(10, 650, 90, 32);
	s->par.pr_tex[9] = create_text(s, "Refraction", 2, 32);
	s->par.pr_pr_rect[9] = make_rect(120, 650, 60, 32);
	s->par.pr_prop[9] = tf(s, 0, 2, 32);
}

void				parab_prop(t_view *s)
{
	s->par.pr_tex = (SDL_Texture **)malloc(sizeof(SDL_Texture*) * NUM_PR_PR);
	s->par.pr_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect) * NUM_PR_PR);
	s->par.pr_pr_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect) * NUM_PR_PR);
	s->par.pr_prop = (SDL_Texture **)malloc(sizeof(SDL_Texture*) * NUM_PR_PR);
	s->par.pr_rect[0] = make_rect(10, 200, 100, 32);
	s->par.pr_tex[0] = create_text(s, "Position-X", 2, 32);
	s->par.pr_pr_rect[0] = make_rect(120, 200, 60, 32);
	s->par.pr_prop[0] = tf(s, 0, 2, 32);
	s->par.pr_rect[1] = make_rect(10, 250, 100, 32);
	s->par.pr_tex[1] = create_text(s, "Position-Y", 2, 32);
	s->par.pr_pr_rect[1] = make_rect(120, 250, 60, 32);
	s->par.pr_prop[1] = tf(s, 0, 2, 32);
	s->par.pr_rect[2] = make_rect(10, 300, 100, 32);
	s->par.pr_tex[2] = create_text(s, "Position-Z", 2, 32);
	s->par.pr_pr_rect[2] = make_rect(120, 300, 60, 32);
	s->par.pr_prop[2] = tf(s, 0, 2, 32);
	s->par.pr_rect[3] = make_rect(10, 350, 70, 32);
	s->par.pr_tex[3] = create_text(s, "Radius", 2, 32);
	s->par.pr_pr_rect[3] = make_rect(120, 350, 60, 32);
	s->par.pr_prop[3] = tf(s, 0, 2, 32);
	parab_prop2(s);
}

void				init_parab_prop(t_view *s)
{
	t_col	c;

	c = col_parse(s->space->cl_figures[s->rr.fl.y].color);
	s->sl[0]->slider_rect.x = c.red;
	s->sl[0]->clr.red = s->sl[0]->slider_rect.x;
	s->sl[1]->slider_rect.x = c.green;
	s->sl[1]->clr.green = s->sl[1]->slider_rect.x;
	s->sl[2]->slider_rect.x = c.blue;
	s->sl[2]->clr.blue = s->sl[2]->slider_rect.x;
	s->par.pr_prop[0] = tf(s,
		s->space->cl_figures[s->rr.fl.y].position.x, 2, 32);
	s->par.pr_prop[1] = tf(s,
		s->space->cl_figures[s->rr.fl.y].position.y, 2, 32);
	s->par.pr_prop[2] = tf(s,
		s->space->cl_figures[s->rr.fl.y].position.z, 2, 32);
	s->par.pr_prop[3] = tf(s, s->space->cl_figures[s->rr.fl.y].radius, 2, 32);
	s->par.pr_prop[4] = tf(s,
		s->space->cl_figures[s->rr.fl.y].reflection, 2, 32);
	s->par.pr_prop[5] = NULL;
	s->par.pr_prop[6] = NULL;
	s->par.pr_prop[7] = NULL;
	s->par.pr_prop[8] = tf(s, s->space->cl_figures[s->rr.fl.y].mirror, 2, 32);
	s->par.pr_prop[9] = tf(s, s->space->cl_figures[s->rr.fl.y].refract, 2, 32);
}

void				print_parab_prop(t_view *s)
{
	int i;

	i = 0;
	SDL_RenderClear(s->rr.rend[2]);
	while (i < NUM_PR_PR && s->flag == 0)
	{
		SDL_RenderCopy(s->rr.rend[2], s->par.pr_tex[i],
			NULL, &s->par.pr_rect[i]);
		SDL_RenderCopy(s->rr.rend[2], s->par.pr_prop[i],
			NULL, &s->par.pr_pr_rect[i]);
		SDL_RenderCopy(s->rr.rend[2], s->ok->b_ok, NULL, &s->ok->ok_rect);
		display_colored_rect(s);
		i++;
	}
	SDL_SetRenderDrawColor(s->rr.rend[2], 10, 20, 40, 255);
	SDL_RenderPresent(s->rr.rend[2]);
}

void				clean_parab_prop(t_view *s)
{
	int	i;

	i = -1;
	while (++i < NUM_PR_PR)
	{
		if (s->par.pr_tex[i])
		{
			SDL_DestroyTexture(s->par.pr_tex[i]);
			s->par.pr_tex[i] = NULL;
		}
		if (s->par.pr_prop[i])
		{
			SDL_DestroyTexture(s->par.pr_prop[i]);
			s->par.pr_prop[i] = NULL;
		}
	}
}
