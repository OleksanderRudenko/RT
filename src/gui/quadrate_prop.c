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

void	quadraate_prop(t_view *s)
{
	// s->qua qu*(t_quad_prop*)malloc(sizeof(t_quad_prop));

	s->qua.qu_tex = (SDL_Texture **)malloc(sizeof(SDL_Texture*) * NUM_QUA_PR);
	s->qua.qu_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect) * NUM_QUA_PR);
	s->qua.qu_pr_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect) * NUM_QUA_PR);
	s->qua.qu_prop = (SDL_Texture **)malloc(sizeof(SDL_Texture*) * NUM_QUA_PR);
	s->qua.qu_rect[0] = make_rect(10, 200, 100, 32);
	s->qua.qu_tex[0] = create_text(s, "Normale-X", 2, 32);
	s->qua.qu_pr_rect[0] = make_rect(120, 200, 60, 32);
	s->qua.qu_prop[0] =  tf(s, 0, 2, 32);
	s->qua.qu_rect[1] = make_rect(10, 250, 100, 32);
	s->qua.qu_tex[1] = create_text(s, "Normale-Y", 2, 32);
	s->qua.qu_pr_rect[1] = make_rect(120, 250, 60, 32);
	s->qua.qu_prop[1] =  tf(s, 0, 2, 32);
	s->qua.qu_rect[2] = make_rect(10, 300, 100, 32);
	s->qua.qu_tex[2] = create_text(s, "Normale-Z", 2, 32);
	s->qua.qu_pr_rect[2] = make_rect(120, 300, 60, 32);
	s->qua.qu_prop[2] =  tf(s, 0, 2, 32);
	s->qua.qu_rect[3] = make_rect(10, 400, 100, 32);
	s->qua.qu_tex[3] = create_text(s, "Reflection", 2, 32);
	s->qua.qu_pr_rect[3] = make_rect(120, 400, 60, 32);
	s->qua.qu_prop[3] =  tf(s, 0, 2, 32);
}

void	init_quadraate_prop(t_view *s)
{
	t_col	c;

	c = col_parse(s->space->cl_figures[s->rr.fl.y].color);
	s->sl[0]->slider_rect.x = c.red;
	s->sl[0]->clr.red = s->sl[0]->slider_rect.x;
	s->sl[1]->slider_rect.x = c.green;
	s->sl[1]->clr.green = s->sl[1]->slider_rect.x;
	s->sl[2]->slider_rect.x = c.blue;
	s->sl[2]->clr.blue = s->sl[2]->slider_rect.x;
	s->qua.qu_prop[0] = tf(s, s->space->cl_figures[s->rr.fl.y].normale.x, 2, 32);
	s->qua.qu_prop[1] = tf(s, s->space->cl_figures[s->rr.fl.y].normale.y, 2, 32);
	s->qua.qu_prop[2] = tf(s, s->space->cl_figures[s->rr.fl.y].normale.z, 2, 32);
	s->qua.qu_prop[3] = tf(s, s->space->cl_figures[s->rr.fl.y].reflection, 2, 32);
}

void	print_quadraate_prop(t_view *s)
{
	int i;

	i = -1;
	SDL_RenderClear(s->rr.rend[2]);
	while (++i < NUM_QUA_PR && s->flag == 0)
	{
		SDL_RenderCopy(s->rr.rend[2], s->qua.qu_tex[i], NULL, &s->qua.qu_rect[i]);
		SDL_RenderCopy(s->rr.rend[2], s->qua.qu_prop[i], NULL, &s->qua.qu_pr_rect[i]);
		SDL_RenderCopy(s->rr.rend[2], s->ok->b_ok, NULL, &s->ok->ok_rect);
		display_colored_rect(s);
	}
	SDL_RenderPresent(s->rr.rend[2]);
}

void	clean_quadraate_prop(t_view *s)
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
