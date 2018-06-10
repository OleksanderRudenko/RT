/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 11:06:45 by arudenko          #+#    #+#             */
/*   Updated: 2018/06/10 13:40:57 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

unsigned int	*get_textures(SDL_Surface **surf, int len)
{
	unsigned int	*array;

	array = (unsigned int *)malloc(sizeof(unsigned int) * (len * 5));
	ft_memcpy(array, surf[0]->pixels, len);
	ft_memcpy(&array[len], surf[1]->pixels, len);
	ft_memcpy(&array[len * 2], surf[2]->pixels, len);
	ft_memcpy(&array[len * 3], surf[3]->pixels, len);
	ft_memcpy(&array[len * 4], perlin_noise(), len);
	return (array);
}

unsigned int	*array_ret(void)
{
	SDL_Surface		**surf;
	unsigned int	*array;
	int				i;
	int				len;

	surf = (SDL_Surface **)malloc(sizeof(SDL_Surface*) * 4);
	surf[0] = IMG_Load("img/one.jpeg");
	surf[1] = IMG_Load("img/two.jpeg");
	surf[2] = IMG_Load("img/three.jpeg");
	surf[3] = IMG_Load("img/four.jpeg");
	if (!surf[0] || !surf[1] || !surf[2] || !surf[3])
		sdl_init_err();
	i = -1;
	while (++i < 4)
		surf[i] = SDL_ConvertSurfaceFormat(surf[i],
								SDL_PIXELFORMAT_ARGB8888, 0);
	len = surf[0]->pitch * surf[0]->h;
	printf("%d\n", surf[0]->pitch);
	printf("%d\n", surf[0]->h);
	array = get_textures(surf, len);
	SDL_FreeSurface(surf[0]);
	SDL_FreeSurface(surf[1]);
	SDL_FreeSurface(surf[2]);
	SDL_FreeSurface(surf[3]);
	return (array);
}
