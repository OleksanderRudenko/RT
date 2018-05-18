/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 16:16:40 by arudenko          #+#    #+#             */
/*   Updated: 2018/04/26 16:16:42 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

SDL_Texture	*create_text(t_view *s, char *name, int i)
{
	t_text t;

	t.font = TTF_OpenFont("Roboto-Black.ttf", 32);
	if (t.font == NULL)
	{
		ft_putendl(TTF_GetError());
	}
	t.color = (SDL_Color){100, 100, 100, 0};
	t.message = TTF_RenderText_Solid(t.font, name, t.color);
	t.tex = SDL_CreateTextureFromSurface(s->rr.rend[i], t.message);
	SDL_FreeSurface(t.message);
	return (t.tex);
}
