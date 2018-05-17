/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_properties.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 15:33:39 by arudenko          #+#    #+#             */
/*   Updated: 2018/05/01 15:33:41 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#define NUM_SPH_PROP 3
/*winID == 3*/

void	sphere_prop(t_view *s)
{
	TTF_Font *font;

	if (!(font = TTF_OpenFont("Roboto-Black.ttf", 32)))
		sdl_ttf_err();
	s->l_prop.prop_tex = (SDL_Texture **)malloc(sizeof(SDL_Texture*) * NUM_SPH_PROP);
	s->l_prop.prop_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect) * NUM_SPH_PROP);

	s->l_prop.prop_rect[0] = make_rect(10, 0, 100, 32);
	s->l_prop.prop_tex[0] = create_text(s, "X-Coordinate", 2);

	s->l_prop.prop_rect[1] = make_rect(10, 50, 100, 32);
	s->l_prop.prop_tex[1] = create_text(s, "Y-Coordinate", 2);

	s->l_prop.prop_rect[2] = make_rect(10, 100, 100, 32);
	s->l_prop.prop_tex[2] = create_text(s, "Z-Coordinate", 2);
}

/*this is a half of function
TODO: display current position, color...*/

void	print_shper_prop(t_view *s)
{
	int i;

	i = -1;
	SDL_RenderClear(s->rr.rend[2]);
	while (++i < NUM_SPH_PROP)
	{
		SDL_RenderCopy(s->rr.rend[2], s->l_prop.prop_tex[i], NULL, &s->l_prop.prop_rect[i]);
	}
	SDL_RenderPresent(s->rr.rend[2]);
}