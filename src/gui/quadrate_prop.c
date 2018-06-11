/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadrate_prop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 14:28:09 by arudenko          #+#    #+#             */
/*   Updated: 2018/05/21 14:28:11 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void inline	quad2(t_view *s)
{
	s->qua.qu_rect[4] = make_rect(80, 400, 100, 32);
	s->qua.qu_tex[4] = create_text(s, "Rotate-Y", 2, 32);
	s->qua.qu_pr_rect[4] = make_rect(120, 400, 60, 32);
	s->qua.qu_prop[4] = NULL;
	s->qua.qu_rect[5] = make_rect(80, 450, 100, 32);
	s->qua.qu_tex[5] = create_text(s, "Rotate-Z", 2, 32);
	s->qua.qu_pr_rect[5] = make_rect(120, 450, 60, 32);
	s->qua.qu_prop[5] = NULL;
	s->qua.qu_rect[6] = make_rect(10, 500, 100, 32);
	s->qua.qu_tex[6] = create_text(s, "Reflection", 2, 32);
	s->qua.qu_pr_rect[6] = make_rect(120, 500, 60, 32);
	s->qua.qu_prop[6] = tf(s, 0, 2, 32);
	s->qua.qu_rect[7] = make_rect(10, 550, 60, 32);
	s->qua.qu_tex[7] = create_text(s, "Mirror", 2, 32);
	s->qua.qu_pr_rect[7] = make_rect(120, 550, 60, 32);
	s->qua.qu_prop[7] = tf(s, 0, 2, 32);
	s->qua.qu_rect[8] = make_rect(10, 600, 100, 32);
	s->qua.qu_tex[8] = create_text(s, "Texture-id", 2, 32);
	s->qua.qu_pr_rect[8] = make_rect(120, 600, 60, 32);
	s->qua.qu_prop[8] = tf(s, 0, 2, 32);
	s->qua.qu_rect[9] = make_rect(10, 650, 90, 32);
	s->qua.qu_tex[9] = create_text(s, "Refraction", 2, 32);
	s->qua.qu_pr_rect[9] = make_rect(120, 650, 60, 32);
	s->qua.qu_prop[9] = tf(s, 0, 2, 32);
}

void				quadraate_prop(t_view *s)
{
	s->qua.qu_tex = (SDL_Texture **)malloc(sizeof(SDL_Texture*) * NUM_QUA_PR);
	s->qua.qu_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect) * NUM_QUA_PR);
	s->qua.qu_pr_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect) * NUM_QUA_PR);
	s->qua.qu_prop = (SDL_Texture **)malloc(sizeof(SDL_Texture*) * NUM_QUA_PR);
	s->qua.qu_rect[0] = make_rect(10, 200, 100, 32);
	s->qua.qu_tex[0] = create_text(s, "Position-X", 2, 32);
	s->qua.qu_pr_rect[0] = make_rect(120, 200, 60, 32);
	s->qua.qu_prop[0] = NULL;
	s->qua.qu_rect[1] = make_rect(10, 250, 100, 32);
	s->qua.qu_tex[1] = create_text(s, "Position-Y", 2, 32);
	s->qua.qu_pr_rect[1] = make_rect(120, 250, 60, 32);
	s->qua.qu_prop[1] = NULL;
	s->qua.qu_rect[2] = make_rect(10, 300, 100, 32);
	s->qua.qu_tex[2] = create_text(s, "Position-Z", 2, 32);
	s->qua.qu_pr_rect[2] = make_rect(120, 300, 60, 32);
	s->qua.qu_prop[2] = NULL;
	s->qua.qu_rect[3] = make_rect(80, 350, 100, 32);
	s->qua.qu_tex[3] = create_text(s, "Rotate-X", 2, 32);
	s->qua.qu_pr_rect[3] = make_rect(120, 350, 60, 32);
	s->qua.qu_prop[3] = NULL;
	quad2(s);
}

void				init_quadraate_prop(t_view *s)
{
	t_col	c;

	c = col_parse(s->space->cl_figures[s->rr.fl.y].color);
	s->sl[0]->slider_rect.x = c.red;
	s->sl[0]->clr.red = s->sl[0]->slider_rect.x;
	s->sl[1]->slider_rect.x = c.green;
	s->sl[1]->clr.green = s->sl[1]->slider_rect.x;
	s->sl[2]->slider_rect.x = c.blue;
	s->sl[2]->clr.blue = s->sl[2]->slider_rect.x;
	s->qua.qu_prop[0] = tf(s,
		s->space->cl_figures[s->rr.fl.y].position.x, 2, 32);
	s->qua.qu_prop[1] = tf(s,
		s->space->cl_figures[s->rr.fl.y].position.y, 2, 32);
	s->qua.qu_prop[2] = tf(s,
		s->space->cl_figures[s->rr.fl.y].position.z, 2, 32);
	s->qua.qu_prop[3] = NULL;
	s->qua.qu_prop[4] = NULL;
	s->qua.qu_prop[5] = NULL;
	s->qua.qu_prop[6] = tf(s,
		s->space->cl_figures[s->rr.fl.y].reflection, 2, 32);
	s->qua.qu_prop[7] = tf(s, s->space->cl_figures[s->rr.fl.y].mirror, 2, 32);
	s->qua.qu_prop[8] = tf(s, s->space->cl_figures[s->rr.fl.y].texture, 2, 32);
	s->qua.qu_prop[9] = tf(s, s->space->cl_figures[s->rr.fl.y].refract, 2, 32);
}

void				print_quadraate_prop(t_view *s)
{
	int i;

	i = -1;
	SDL_RenderClear(s->rr.rend[2]);
	while (++i < NUM_QUA_PR && s->flag == 0)
	{
		SDL_RenderCopy(s->rr.rend[2], s->qua.qu_tex[i],
			NULL, &s->qua.qu_rect[i]);
		SDL_RenderCopy(s->rr.rend[2], s->qua.qu_prop[i],
			NULL, &s->qua.qu_pr_rect[i]);
		SDL_RenderCopy(s->rr.rend[2], s->ok->b_ok, NULL, &s->ok->ok_rect);
		display_colored_rect(s);
	}
	SDL_SetRenderDrawColor(s->rr.rend[2], 10, 20, 40, 255);
	SDL_RenderPresent(s->rr.rend[2]);
}

void				clean_quadraate_prop(t_view *s)
{
	int	i;

	i = -1;
	while (++i < NUM_QUA_PR)
	{
		if (s->qua.qu_tex[i])
		{
			SDL_DestroyTexture(s->qua.qu_tex[i]);
			s->qua.qu_tex[i] = NULL;
		}
		if (s->qua.qu_prop[i])
		{
			SDL_DestroyTexture(s->qua.qu_prop[i]);
			s->qua.qu_prop[i] = NULL;
		}
	}
}
