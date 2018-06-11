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

SDL_Texture	*create_text(t_view *s, char *name, int i, int font_size)
{
	t_text t;

	t.font = TTF_OpenFont("Roboto-Regular.ttf", font_size);
	if (t.font == NULL)
	{
		sdl_ttf_err();
	}
	t.color = (SDL_Color){100, 100, 100, 0};
	t.message = TTF_RenderText_Solid(t.font, name, t.color);
	t.tex = SDL_CreateTextureFromSurface(s->rr.rend[i], t.message);
	SDL_FreeSurface(t.message);
	t.message = NULL;
	TTF_CloseFont(t.font);
	return (t.tex);
}

SDL_Texture	*get_tex(char *file, SDL_Renderer *ren_tar)
{
	SDL_Texture *texture;
	SDL_Surface *surface;

	surface = IMG_Load(file);
	if (surface == NULL)
		sdl_img_err();
	texture = SDL_CreateTextureFromSurface(ren_tar, surface);
	if (texture == NULL)
	{
		ft_putendl(SDL_GetError());
		exit(0);
	}
	SDL_FreeSurface(surface);
	return (texture);
}

SDL_Surface	*get_valid_texture(char *file)
{
	SDL_Surface *surface;

	surface = IMG_Load(file);
	if (surface == NULL)
		sdl_img_err();
	if (surface->w != 256 && surface->w != 256
		&& surface->format->BytesPerPixel != 4)
		sdl_texture_valid_error();
	return (surface);
}

SDL_Texture	*tf(t_view *s, float num, int i, int font_size)
{
	t_text	t;
	char	*arr;

	t.font = TTF_OpenFont("Roboto-Regular.ttf", font_size);
	if (t.font == NULL)
	{
		sdl_ttf_err();
	}
	t.color = (SDL_Color){150, 100, 0, 0};
	arr = ft_ftoa(num);
	t.message = TTF_RenderText_Solid(t.font, arr, t.color);
	t.tex = SDL_CreateTextureFromSurface(s->rr.rend[i], t.message);
	SDL_FreeSurface(t.message);
	t.message = NULL;
	free(arr);
	TTF_CloseFont(t.font);
	return (t.tex);
}

int			text_width(TTF_Font *f, char *str)
{
	char		*buf;
	int			width;
	int			len;

	len = ft_strlen(str);
	if (len > MAX_TEXT_LEN)
		len = 149;
	buf = ft_strnew(MAX_TEXT_LEN);
	ft_strncpy(buf, str, len);
	TTF_SizeUTF8(f, buf, &width, NULL);
	free(buf);
	return (width);
}
