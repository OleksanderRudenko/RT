/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_prop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 14:24:39 by arudenko          #+#    #+#             */
/*   Updated: 2018/05/21 14:24:40 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static inline void	plane_prop2(t_view *s)
{
	s->pl.pl_rect[4] = make_rect(80, 400, 80, 32);
	s->pl.pl_tex[4] = create_text(s, "Rotate-X", 2, 32);
	s->pl.pl_pr_rect[4] = make_rect(120, 400, 60, 32);
	s->pl.pl_prop[4] = NULL;
	s->pl.pl_rect[5] = make_rect(80, 450, 80, 32);
	s->pl.pl_tex[5] = create_text(s, "Rotate-Y", 2, 32);
	s->pl.pl_pr_rect[5] = make_rect(120, 450, 60, 32);
	s->pl.pl_prop[5] = NULL;
	s->pl.pl_rect[6] = make_rect(80, 500, 80, 32);
	s->pl.pl_tex[6] = create_text(s, "Rotate-Z", 2, 32);
	s->pl.pl_pr_rect[6] = make_rect(120, 500, 60, 32);
	s->pl.pl_prop[6] = NULL;
	s->pl.pl_rect[7] = make_rect(10, 550, 60, 32);
	s->pl.pl_tex[7] = create_text(s, "Mirror", 2, 32);
	s->pl.pl_pr_rect[7] = make_rect(120, 550, 60, 32);
	s->pl.pl_prop[7] = tf(s, 0, 2, 32);
	s->pl.pl_rect[8] = make_rect(10, 600, 100, 32);
	s->pl.pl_tex[8] = create_text(s, "Texture-id", 2, 32);
	s->pl.pl_pr_rect[8] = make_rect(120, 600, 60, 32);
	s->pl.pl_prop[8] = tf(s, 0, 2, 32);
	s->pl.pl_rect[9] = make_rect(10, 650, 90, 32);
	s->pl.pl_tex[9] = create_text(s, "Refraction", 2, 32);
	s->pl.pl_pr_rect[9] = make_rect(120, 650, 60, 32);
	s->pl.pl_prop[9] = tf(s, 0, 2, 32);
}

void				plane_prop(t_view *s)
{
	s->pl.pl_tex = (SDL_Texture **)malloc(sizeof(SDL_Texture*) * NUM_PL_PR);
	s->pl.pl_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect) * NUM_PL_PR);
	s->pl.pl_pr_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect) * NUM_PL_PR);
	s->pl.pl_prop = (SDL_Texture **)malloc(sizeof(SDL_Texture*) * NUM_PL_PR);
	s->pl.pl_rect[0] = make_rect(10, 200, 80, 32);
	s->pl.pl_tex[0] = create_text(s, "Point-X", 2, 32);
	s->pl.pl_pr_rect[0] = make_rect(120, 200, 60, 32);
	s->pl.pl_prop[0] = tf(s, 0, 2, 32);
	s->pl.pl_rect[1] = make_rect(10, 250, 80, 32);
	s->pl.pl_tex[1] = create_text(s, "Point-Y", 2, 32);
	s->pl.pl_pr_rect[1] = make_rect(120, 250, 60, 32);
	s->pl.pl_prop[1] = tf(s, 0, 2, 32);
	s->pl.pl_rect[2] = make_rect(10, 300, 80, 32);
	s->pl.pl_tex[2] = create_text(s, "Point-Z", 2, 32);
	s->pl.pl_pr_rect[2] = make_rect(120, 300, 60, 32);
	s->pl.pl_prop[2] = tf(s, 0, 2, 32);
	s->pl.pl_rect[3] = make_rect(10, 350, 100, 32);
	s->pl.pl_tex[3] = create_text(s, "Reflection", 2, 32);
	s->pl.pl_pr_rect[3] = make_rect(120, 350, 60, 32);
	s->pl.pl_prop[3] = tf(s, 0, 2, 32);
	plane_prop2(s);
}

void				init_plane_prop(t_view *s)
{
	t_col	c;

	c = col_parse(s->space->cl_figures[s->rr.fl.y].color);
	s->sl[0]->slider_rect.x = c.red;
	s->sl[0]->clr.red = s->sl[0]->slider_rect.x;
	s->sl[1]->slider_rect.x = c.green;
	s->sl[1]->clr.green = s->sl[1]->slider_rect.x;
	s->sl[2]->slider_rect.x = c.blue;
	s->sl[2]->clr.blue = s->sl[2]->slider_rect.x;
	s->pl.pl_prop[0] = tf(s, s->space->cl_figures[s->rr.fl.y].point.x, 2, 32);
	s->pl.pl_prop[1] = tf(s, s->space->cl_figures[s->rr.fl.y].point.y, 2, 32);
	s->pl.pl_prop[2] = tf(s, s->space->cl_figures[s->rr.fl.y].point.z, 2, 32);
	s->pl.pl_prop[3] = tf(s,
		s->space->cl_figures[s->rr.fl.y].reflection, 2, 32);
	s->pl.pl_prop[4] = NULL;
	s->pl.pl_prop[5] = NULL;
	s->pl.pl_prop[6] = NULL;
	s->pl.pl_prop[7] = tf(s, s->space->cl_figures[s->rr.fl.y].mirror, 2, 32);
	s->pl.pl_prop[8] = tf(s, s->space->cl_figures[s->rr.fl.y].texture, 2, 32);
	s->pl.pl_prop[9] = tf(s, s->space->cl_figures[s->rr.fl.y].refract, 2, 32);
}

void				print_pl_prop(t_view *s)
{
	int i;

	i = -1;
	SDL_RenderClear(s->rr.rend[2]);
	while (++i < NUM_PL_PR && s->flag == 0)
	{
		SDL_RenderCopy(s->rr.rend[2], s->pl.pl_tex[i],
			NULL, &s->pl.pl_rect[i]);
		SDL_RenderCopy(s->rr.rend[2], s->pl.pl_prop[i],
			NULL, &s->pl.pl_pr_rect[i]);
		SDL_RenderCopy(s->rr.rend[2], s->ok->b_ok, NULL, &s->ok->ok_rect);
		display_colored_rect(s);
	}
	SDL_SetRenderDrawColor(s->rr.rend[2], 10, 20, 40, 255);
	SDL_RenderPresent(s->rr.rend[2]);
}

void				clean_plane_prop(t_view *s)
{
	int	i;

	i = -1;
	while (++i < NUM_PL_PR)
	{
		if (s->pl.pl_tex[i])
		{
			SDL_DestroyTexture(s->pl.pl_tex[i]);
			s->pl.pl_tex[i] = NULL;
		}
		if (s->pl.pl_prop[i])
		{
			SDL_DestroyTexture(s->pl.pl_prop[i]);
			s->pl.pl_prop[i] = NULL;
		}
	}
}
