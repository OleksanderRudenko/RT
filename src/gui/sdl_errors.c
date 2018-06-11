/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 13:30:38 by arudenko          #+#    #+#             */
/*   Updated: 2018/04/26 13:30:43 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	sdl_init_err(void)
{
	ft_putendl(SDL_GetError());
	exit(0);
}

void	sdl_ttf_err(void)
{
	ft_putendl(TTF_GetError());
	exit(0);
}

void	sdl_img_err(void)
{
	ft_putendl(IMG_GetError());
	exit(0);
}

void	sdl_texture_valid_error(void)
{
	ft_putendl("Invalid Texture HERE");
	exit(0);
}
