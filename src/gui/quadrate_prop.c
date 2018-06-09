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
	s->qua.qu_tex = (SDL_Texture **)ft_memalloc(sizeof(SDL_Texture*) * NUM_QUA_PR);
	s->qua.qu_rect = (SDL_Rect *)ft_memalloc(sizeof(SDL_Rect) * NUM_QUA_PR);
	s->qua.qu_pr_rect = (SDL_Rect *)ft_memalloc(sizeof(SDL_Rect) * NUM_QUA_PR);
	s->qua.qu_prop = (SDL_Texture **)ft_memalloc(sizeof(SDL_Texture*) * NUM_QUA_PR);
	s->qua.qu_rect[0] = make_rect(80, 200, 100, 32);
	s->qua.qu_tex[0] = create_text(s, "Rotate-X", 2, 32);
	s->qua.qu_pr_rect[0] = make_rect(120, 200, 60, 32);
	s->qua.qu_prop[0] = NULL;
	s->qua.qu_rect[1] = make_rect(80, 250, 100, 32);
	s->qua.qu_tex[1] = create_text(s, "Rotate-Y", 2, 32);
	s->qua.qu_pr_rect[1] = make_rect(120, 250, 60, 32);
	s->qua.qu_prop[1] = NULL;
	s->qua.qu_rect[2] = make_rect(80, 300, 100, 32);
	s->qua.qu_tex[2] = create_text(s, "Rotate-Z", 2, 32);
	s->qua.qu_pr_rect[2] = make_rect(120, 300, 60, 32);
	s->qua.qu_prop[2] = NULL;
	s->qua.qu_rect[3] = make_rect(10, 350, 100, 32);
	s->qua.qu_tex[3] = create_text(s, "Reflection", 2, 32);
	s->qua.qu_pr_rect[3] = make_rect(120, 350, 60, 32);
	s->qua.qu_prop[3] =  tf(s, 0, 2, 32);
	s->qua.qu_rect[4] = make_rect(10, 400, 60, 32);
	s->qua.qu_tex[4] = create_text(s, "Mirror", 2, 32);
	s->qua.qu_pr_rect[4] = make_rect(120, 400, 60, 32);
	s->qua.qu_prop[4] =  tf(s, 0, 2, 32);
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
	s->qua.qu_prop[0] = NULL;
	s->qua.qu_prop[1] = NULL;
	s->qua.qu_prop[2] = NULL;
	s->qua.qu_prop[3] = tf(s, s->space->cl_figures[s->rr.fl.y].reflection, 2, 32);
	s->qua.qu_prop[4] = tf(s, s->space->cl_figures[s->rr.fl.y].mirror, 2, 32);
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
	SDL_SetRenderDrawColor(s->rr.rend[2], 10, 20, 40, 255);
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
