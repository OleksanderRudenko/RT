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
	s->prop.rect[3] = make_rect(10, 350, 100, 32);
	s->prop.tex[3] = create_text(s, "Radius", 2, 32);
	s->prop.pr_rect[3] = make_rect(120, 350, 60, 32);
	s->prop.prop[3] =  create_text_ftoa(s, 0, 2, 32);

	s->prop.rect[4] = make_rect(10, 400, 100, 32);
	s->prop.tex[4] = create_text(s, "Reflection", 2, 32);
	s->prop.pr_rect[4] = make_rect(120, 400, 60, 32);
	s->prop.prop[4] =  create_text_ftoa(s, 0, 2, 32);

	// s->prop.rect[5] = make_rect(10, 250, 100, 32);
	// s->prop.tex[5] = create_text(s, "Red color", 2, 32);
	// s->prop.pr_rect[5] = make_rect(120, 250, 60, 32);
	// s->prop.prop[5] =  create_text_ftoa(s, 0, 2, 32);

	// s->prop.rect[6] = make_rect(10, 300, 100, 32);
	// s->prop.tex[6] = create_text(s, "Green color", 2, 32);
	// s->prop.pr_rect[6] = make_rect(120, 300, 60, 32);
	// s->prop.prop[6] =  create_text_ftoa(s, 0, 2, 32);

	// s->prop.rect[7] = make_rect(10, 350, 100, 32);
	// s->prop.tex[7] = create_text(s, "Blue color", 2, 32);
	// s->prop.pr_rect[7] = make_rect(120, 350, 60, 32);
	// s->prop.prop[7] =  create_text_ftoa(s, 0, 2, 32);
}

void	sphere_prop(t_view *s)
{
	s->prop.tex = (SDL_Texture **)malloc(sizeof(SDL_Texture*) * NUM_SPH_PROP);
	s->prop.rect = (SDL_Rect *)malloc(sizeof(SDL_Rect) * NUM_SPH_PROP);
	s->prop.pr_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect) * NUM_SPH_PROP);
	s->prop.prop = (SDL_Texture **)malloc(sizeof(SDL_Texture*) * NUM_SPH_PROP);

	s->prop.rect[0] = make_rect(10, 200, 100, 32);
	s->prop.tex[0] = create_text(s, "X-Coordinate", 2, 32);
	s->prop.pr_rect[0] = make_rect(120, 200, 60, 32);
	s->prop.prop[0] =  create_text_ftoa(s, 0, 2, 32);

	s->prop.rect[1] = make_rect(10, 250, 100, 32);
	s->prop.tex[1] = create_text(s, "Y-Coordinate", 2, 32);
	s->prop.pr_rect[1] = make_rect(120, 250, 60, 32);
	s->prop.prop[1] =  create_text_ftoa(s, 0, 2, 32);

	s->prop.rect[2] = make_rect(10, 300, 100, 32);
	s->prop.tex[2] = create_text(s, "Z-Coordinate", 2, 32);
	s->prop.pr_rect[2] = make_rect(120, 300, 60, 32);
	s->prop.prop[2] =  create_text_ftoa(s, 0, 2, 32);
	sphere_prop2(s);
}

void	init_sphere_prop(t_view *s, t_sphere *f, t_figure *fig)
{
	t_col	c;

	c = col_parse(fig->color);
	s->sl[0]->slider_rect.x = c.red;
	s->sl[0]->clr.red = s->sl[0]->slider_rect.x;
	s->sl[1]->slider_rect.x = c.green;
	s->sl[1]->clr.green = s->sl[1]->slider_rect.x;
	s->sl[2]->slider_rect.x = c.blue;
	s->sl[2]->clr.blue = s->sl[2]->slider_rect.x;
	s->prop.prop[0] =  create_text_ftoa(s, f->center.x , 2, 32);
	s->prop.prop[1] =  create_text_ftoa(s, f->center.y , 2, 32);
	s->prop.prop[2] =  create_text_ftoa(s, f->center.z , 2, 32);
	s->prop.prop[3] =  create_text_ftoa(s, f->radius , 2, 32);
	s->prop.prop[4] =  create_text_ftoa(s, fig->reflection , 2, 32);
	s->prop.prop[5] =  create_text_ftoa(s, c.red, 2, 32);
	s->prop.prop[6] =  create_text_ftoa(s, c.green, 2, 32);
	s->prop.prop[7] =  create_text_ftoa(s, c.blue, 2, 32);
}

void	print_prop(t_view *s)
{
	int i;
	t_figure	*fig;

	i = -1;
	fig = detect_figure(s);
	SDL_RenderClear(s->rr.rend[2]);
	/* TODO: NUM_OVERALL PROP*/
	while (++i < 5 && s->flag == 0)
	{
		SDL_RenderCopy(s->rr.rend[2], s->prop.tex[i], NULL, &s->prop.rect[i]);
		SDL_RenderCopy(s->rr.rend[2], s->prop.prop[i], NULL, &s->prop.pr_rect[i]);
		SDL_RenderCopy(s->rr.rend[2], s->ok->b_ok, NULL, &s->ok->ok_rect);
		display_colored_rect(s);
		fig->type == Sphere ? p_sp_prop(s, NUM_SPH_PROP, s->prop.prop, s->prop.pr_rect) : 0;
	}
	SDL_RenderPresent(s->rr.rend[2]);
}

void	p_sp_prop(t_view *s, int num, SDL_Texture **t, SDL_Rect *r)
{
	int		i;

	i = -1;
	while (++i < num)
		SDL_RenderCopy(s->rr.rend[2], t[i], NULL, &r[i]);
}

void	clean_sphere_prop(t_view *s)
{
	int	i;

	i = 0;
	while (i < NUM_SPH_PROP)
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
		i++;
	}
}

