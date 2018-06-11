/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataranov <ataranov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 11:06:45 by arudenko          #+#    #+#             */
/*   Updated: 2018/06/11 21:02:45 by ataranov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

unsigned int	*get_textures(SDL_Surface **surf, int len)
{
	unsigned int	*array;
	unsigned int	*tmp;

	array = (unsigned int *)malloc(sizeof(unsigned int) * (len * 5));
	ft_memcpy(array, surf[0]->pixels, len);
	ft_memcpy(&array[len], surf[1]->pixels, len);
	ft_memcpy(&array[len * 2], surf[2]->pixels, len);
	ft_memcpy(&array[len * 3], surf[3]->pixels, len);
	tmp = perlin_noise();
	ft_memcpy(&array[len * 4], tmp, len);
	free(tmp);
	return (array);
}

void			clean_trash(SDL_Surface **surf, SDL_Surface **tmp)
{
	int i;

	i = -1;
	while (++i < 4)
	{
		SDL_FreeSurface(surf[i]);
		SDL_FreeSurface(tmp[i]);
	}
	free(tmp);
	free(surf);
}

unsigned int	*array_ret(void)
{
	SDL_Surface		**surf;
	SDL_Surface		**tmp;
	unsigned int	*array;
	int				i;
	int				len;

	surf = (SDL_Surface **)malloc(sizeof(SDL_Surface*) * 4);
	tmp = (SDL_Surface **)malloc(sizeof(SDL_Surface*) * 4);
	surf[0] = get_valid_texture("img/one.jpeg");
	surf[1] = get_valid_texture("img/two.jpeg");
	surf[2] = get_valid_texture("img/three.jpeg");
	surf[3] = get_valid_texture("img/four.jpeg");
	i = -1;
	while (++i < 4)
		tmp[i] = SDL_ConvertSurfaceFormat(surf[i],
								SDL_PIXELFORMAT_ARGB8888, 0);
	len = surf[0]->pitch * surf[0]->h;
	array = get_textures(surf, len);
	clean_trash(surf, tmp);
	return (array);
}
