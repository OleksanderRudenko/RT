/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shpere_prop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 11:12:53 by arudenko          #+#    #+#             */
/*   Updated: 2018/05/14 11:12:55 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static inline void	sphere_prop2(t_view *s)
{
	s->prop.rect[4] = make_rect(10, 400, 100, 30);
	s->prop.tex[4] = create_text(s, "Reflection", 2, 30);
	s->prop.pr_rect[4] = make_rect(150, 400, 60, 30);
	s->prop.prop[4] =  tf(s, 0, 2, 30);
	s->prop.rect[5] = make_rect(10, 450, 60, 30);
	s->prop.tex[5] = create_text(s, "Mirror", 2, 30);
	s->prop.pr_rect[5] = make_rect(150, 450, 60, 30);
	s->prop.prop[5] =  tf(s, 0, 2, 30);
}

void	sphere_prop(t_view *s)
{
	// s->prop = *(t_sp_prop*)malloc(sizeof(t_sp_prop));

	s->prop.tex = (SDL_Texture **)malloc(sizeof(SDL_Texture*) * NUM_SP_PR);
	s->prop.rect = (SDL_Rect *)malloc(sizeof(SDL_Rect) * NUM_SP_PR);
	s->prop.pr_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect) * NUM_SP_PR);
	s->prop.prop = (SDL_Texture **)malloc(sizeof(SDL_Texture*) * NUM_SP_PR);
	s->prop.rect[0] = make_rect(10, 200, ft_strlen("X-Coordinate") * 10, 30);
	s->prop.tex[0] = create_text(s, "X-Coordinate", 2, 30);
	s->prop.pr_rect[0] = make_rect(150, 200, 60, 30);
	s->prop.prop[0] =  tf(s, 0, 2, 30);
	s->prop.rect[1] = make_rect(10, 250, ft_strlen("Y-Coordinate") * 10, 30);
	s->prop.tex[1] = create_text(s, "Y-Coordinate", 2, 30);
	s->prop.pr_rect[1] = make_rect(150, 250, 60, 30);
	s->prop.prop[1] =  tf(s, 0, 2, 30);
	s->prop.rect[2] = make_rect(10, 300, ft_strlen("Z-Coordinate") * 10, 30);
	s->prop.tex[2] = create_text(s, "Z-Coordinate", 2, 30);
	s->prop.pr_rect[2] = make_rect(150, 300, 60, 30);
	s->prop.prop[2] =  tf(s, 0, 2, 30);
	s->prop.rect[3] = make_rect(10, 350, ft_strlen("Radius") * 10, 30);
	s->prop.tex[3] = create_text(s, "Radius", 2, 30);
	s->prop.pr_rect[3] = make_rect(150, 350, 60, 30);
	s->prop.prop[3] =  tf(s, 0, 2, 30);
	sphere_prop2(s);
}

void	init_prop(t_view *s)
{
	t_col	c;
	int		i;

	c = col_parse(s->space->cl_figures[s->rr.fl.y].color);
	s->sl[0]->slider_rect.x = c.red;
	s->sl[0]->clr.red = s->sl[0]->slider_rect.x;
	s->sl[1]->slider_rect.x = c.green;
	s->sl[1]->clr.green = s->sl[1]->slider_rect.x;
	s->sl[2]->slider_rect.x = c.blue;
	s->sl[2]->clr.blue = s->sl[2]->slider_rect.x;
	i = -1;
	while (++i < NUM_SP_PR){
		SDL_DestroyTexture(s->prop.prop[i]);
		s->prop.prop[i] = NULL;
	}
	s->prop.prop[0] = tf(s, s->space->cl_figures[s->rr.fl.y].center.x, 2, 32);
	s->prop.prop[1] = tf(s, s->space->cl_figures[s->rr.fl.y].center.y, 2, 32);
	s->prop.prop[2] = tf(s, s->space->cl_figures[s->rr.fl.y].center.z, 2, 32);
	s->prop.prop[3] = tf(s, s->space->cl_figures[s->rr.fl.y].radius, 2, 32);
	s->prop.prop[4] = tf(s, s->space->cl_figures[s->rr.fl.y].reflection, 2, 32);
	s->prop.prop[5] = tf(s, s->space->cl_figures[s->rr.fl.y].mirror, 2, 32);
	/*MEMORY LEAKS HERE!!! AFTER NEW INIT ts function gives a leak OR NOT ??*/
}

void	print_sph_prop(t_view *s)
{
	int i;

	i = 0;
	SDL_RenderClear(s->rr.rend[2]);
	while (i < NUM_SP_PR && s->flag == 0)
	{
		SDL_RenderCopy(s->rr.rend[2], s->prop.tex[i], NULL, &s->prop.rect[i]);
		SDL_RenderCopy(s->rr.rend[2], s->prop.prop[i], NULL, &s->prop.pr_rect[i]);
		SDL_RenderCopy(s->rr.rend[2], s->ok->b_ok, NULL, &s->ok->ok_rect);
		display_colored_rect(s);
		i++;
	}
	SDL_RenderPresent(s->rr.rend[2]);
}

void	clean_sphere_prop(t_view *s)
{
	int	i;

	i = -1;
	while (++i < NUM_SP_PR)
	{
		if (s->prop.tex[i])
		{
			SDL_DestroyTexture(s->prop.tex[i]);
			s->prop.tex[i] = NULL;
		}
		if (s->prop.prop[i])
		{
			SDL_DestroyTexture(s->prop.prop[i]);
			s->prop.prop[i] = NULL;
		}
	}
	// free(s->prop.rect);/*DO IN ALL OTHER SUCH FILES*/
}
