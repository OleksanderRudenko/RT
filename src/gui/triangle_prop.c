/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_prop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 14:26:56 by arudenko          #+#    #+#             */
/*   Updated: 2018/05/21 14:26:58 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

// static inline void	tr_prop2(t_view *s)
// {
// 	s->tri.tri_rect[4] = make_rect(10, 400, 100, 32);
// 	s->tri.tri_tex[4] = create_text(s, "Reflection", 2, 32);
// 	s->tri.tri_pr_rect[4] = make_rect(120, 400, 60, 32);
// 	s->tri.tri_prop[4] =  tf(s, 0, 2, 32);
// }

void	triangle_prop(t_view *s)
{
	// s->tri = *(t_trial_prop*)malloc(sizeof(t_trial_prop));

	s->tri.tri_tex = (SDL_Texture **)malloc(sizeof(SDL_Texture*) * NUM_TR_PR);
	s->tri.tri_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect) * NUM_TR_PR);
	s->tri.tri_pr_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect) * NUM_TR_PR);
	s->tri.tri_prop = (SDL_Texture **)malloc(sizeof(SDL_Texture*) * NUM_TR_PR);
	s->tri.tri_rect[0] = make_rect(10, 200, 100, 32);
	s->tri.tri_tex[0] = create_text(s, "Normale-X", 2, 32);
	s->tri.tri_pr_rect[0] = make_rect(120, 200, 60, 32);
	s->tri.tri_prop[0] =  tf(s, 0, 2, 32);
	s->tri.tri_rect[1] = make_rect(10, 250, 100, 32);
	s->tri.tri_tex[1] = create_text(s, "Normale-Y", 2, 32);
	s->tri.tri_pr_rect[1] = make_rect(120, 250, 60, 32);
	s->tri.tri_prop[1] =  tf(s, 0, 2, 32);
	s->tri.tri_rect[2] = make_rect(10, 300, 100, 32);
	s->tri.tri_tex[2] = create_text(s, "Normale-Z", 2, 32);
	s->tri.tri_pr_rect[2] = make_rect(120, 300, 60, 32);
	s->tri.tri_prop[2] =  tf(s, 0, 2, 32);
	s->tri.tri_rect[3] = make_rect(10, 350, 100, 32);
	s->tri.tri_tex[3] = create_text(s, "Reflection", 2, 32);
	s->tri.tri_pr_rect[3] = make_rect(120, 350, 60, 32);
	s->tri.tri_prop[3] =  tf(s, 0, 2, 32);
	// tr_prop2(s);
}

void	triangle_init_prop(t_view *s)
{
	t_col	c;

	c = col_parse(s->space->cl_figures[s->rr.fl.y].color);
	s->sl[0]->slider_rect.x = c.red;
	s->sl[0]->clr.red = s->sl[0]->slider_rect.x;
	s->sl[1]->slider_rect.x = c.green;
	s->sl[1]->clr.green = s->sl[1]->slider_rect.x;
	s->sl[2]->slider_rect.x = c.blue;
	s->sl[2]->clr.blue = s->sl[2]->slider_rect.x;
	s->tri.tri_prop[0] = tf(s, s->space->cl_figures[s->rr.fl.y].normale.x, 2, 32);
	s->tri.tri_prop[1] = tf(s, s->space->cl_figures[s->rr.fl.y].normale.y, 2, 32);
	s->tri.tri_prop[2] = tf(s, s->space->cl_figures[s->rr.fl.y].normale.z, 2, 32);
	s->tri.tri_prop[3] = tf(s, s->space->cl_figures[s->rr.fl.y].reflection, 2, 32);
}

void	print_triangle_prop(t_view *s)
{
	int i;

	i = -1;
	SDL_RenderClear(s->rr.rend[2]);
	while (++i < NUM_TR_PR && s->flag == 0)
	{
		SDL_RenderCopy(s->rr.rend[2], s->tri.tri_tex[i], NULL, &s->tri.tri_rect[i]);
		SDL_RenderCopy(s->rr.rend[2], s->tri.tri_prop[i], NULL, &s->tri.tri_pr_rect[i]);
		SDL_RenderCopy(s->rr.rend[2], s->ok->b_ok, NULL, &s->ok->ok_rect);
		display_colored_rect(s);
	}
	SDL_RenderPresent(s->rr.rend[2]);
}

void	clean_triangle_prop(t_view *s)
{
	int	i;

	i = -1;
	while (++i < NUM_TR_PR)
	{
		if (s->tri.tri_tex[i])
		{
			SDL_DestroyTexture(s->tri.tri_tex[i]);
			s->tri.tri_tex[i] = NULL;
		}
		if (s->tri.tri_prop[i])
		{
			SDL_DestroyTexture(s->tri.tri_prop[i]);
			s->tri.tri_prop[i] = NULL;
		}
	}
}

